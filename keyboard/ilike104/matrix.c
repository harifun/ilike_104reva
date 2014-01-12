/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

#define DATA_MAIN 	PIND
#define DATA_NUM	PINB

#define CS_M_SET	PORTF |= 0x20
#define CS_M_CLR	PORTF &= 0xDF
#define SCK_M_SET	PORTF |= 0x40
#define SCK_M_CLR	PORTF &= 0xBF

#define CS_N_SET	PORTF |= 0x01
#define CS_N_CLR	PORTF &= 0xFE
#define SCK_N_SET	PORTF |= 0x02
#define SCK_N_CLR	PORTF &= 0xFD
#define SDI_N_SET	PORTF |= 0x10
#define SDI_N_CLR	PORTF &= 0xEF

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;
uint8_t CODE[14];
static uint8_t flash_ctr = 0x00;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

//IO≥ı ºªØ
void Init_IO(void)
{
	DDRB &= 0x00;
	PORTB |= 0xFF;
	
	DDRD &= 0x00;
	PORTD |= 0xFF;
	
	DDRF |= 0xF3;
	PORTF |= 0xF3;
	
	DDRE |= 0x40;
	PORTE |= 0x40;
	
	DDRC |= 0xC0;
	PORTC |= 0xC0;
}

inline void JTAG_Disable(void)
{
    unsigned char temp = 0;
    temp = MCUCR | (1 << JTD);
    MCUCR = temp;
    MCUCR = temp;
}

void matrix_init(void)
{
	Init_IO();
	JTAG_Disable();
}

void Scan_Main(void)
{
	uint8_t i;
	CS_M_CLR;
	_delay_us(2);
	CS_M_SET;
	_delay_us(2);
	for(i=0;i<8;i++)
	{
		SCK_M_CLR;
		_delay_us(2);
		CODE[i] = DATA_MAIN;
		SCK_M_SET;
		_delay_us(2);
	}
}

void Scan_Num(void)
{
	uint8_t i;
	CS_N_CLR;
	_delay_us(2);
	CS_N_SET;
	_delay_us(2);
	for(i=0;i<6;i++)
	{
		SCK_N_CLR;
		_delay_us(2);
		CODE[i+8] = DATA_NUM;
		SCK_N_SET;
		_delay_us(2);
	}
}

void Write_Flash(void)
{
	uint8_t i;
	CS_N_CLR;
	_delay_us(2);
	CS_N_SET;
	_delay_us(2);
	for(i=0;i<2;i++)
	{
		SCK_N_CLR;
		if(flash_ctr & (1<<(i+6)))
			SDI_N_SET;
		else
			SDI_N_CLR;
		_delay_us(2);
		SCK_N_SET;
		_delay_us(2);
	}	
}

void Keyscan(void)
{
	Scan_Main();
	Scan_Num();
}

uint8_t matrix_scan(void)
{
	Keyscan();

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
 * pin: F0  F1  E6  C7  C6  B6  D4  B1  B0  B5  B4  D7  D6  B3  (Rev.A)
 * pin:                                 B7                      (Rev.B)
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~(1<<0 | 1<<1);
    PORTF |=  (1<<0 | 1<<1);
    DDRE  &= ~(1<<6);
    PORTE |=  (1<<6);
    DDRD  &= ~(1<<7 | 1<<6 | 1<<4);
    PORTD |=  (1<<7 | 1<<6 | 1<<4);
    DDRC  &= ~(1<<7 | 1<<6);
    PORTC |=  (1<<7 | 1<<6);
    DDRB  &= ~(1<<7 | 1<<6 | 1<< 5 | 1<<4 | 1<<3 | 1<<1 | 1<<0);
    PORTB |=  (1<<7 | 1<<6 | 1<< 5 | 1<<4 | 1<<3 | 1<<1 | 1<<0);
}

static matrix_row_t read_cols(void)
{
    return (PINF&(1<<0) ? 0 : (1<<0)) |
           (PINF&(1<<1) ? 0 : (1<<1)) |
           (PINE&(1<<6) ? 0 : (1<<2)) |
           (PINC&(1<<7) ? 0 : (1<<3)) |
           (PINC&(1<<6) ? 0 : (1<<4)) |
           (PINB&(1<<6) ? 0 : (1<<5)) |
           (PIND&(1<<4) ? 0 : (1<<6)) |
           (PINB&(1<<1) ? 0 : (1<<7)) |
           ((PINB&(1<<0) && PINB&(1<<7)) ? 0 : (1<<8)) |     // Rev.A and B
           (PINB&(1<<5) ? 0 : (1<<9)) |
           (PINB&(1<<4) ? 0 : (1<<10)) |
           (PIND&(1<<7) ? 0 : (1<<11)) |
           (PIND&(1<<6) ? 0 : (1<<12)) |
           (PINB&(1<<3) ? 0 : (1<<13));
}

/* Row pin configuration
 * row: 0   1   2   3   4
 * pin: D0  D1  D2  D3  D5
 */
static void unselect_rows(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRD  &= ~0b00101111;
    PORTD &= ~0b00101111;
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
        case 0:
            DDRD  |= (1<<0);
            PORTD &= ~(1<<0);
            break;
        case 1:
            DDRD  |= (1<<1);
            PORTD &= ~(1<<1);
            break;
        case 2:
            DDRD  |= (1<<2);
            PORTD &= ~(1<<2);
            break;
        case 3:
            DDRD  |= (1<<3);
            PORTD &= ~(1<<3);
            break;
        case 4:
            DDRD  |= (1<<5);
            PORTD &= ~(1<<5);
            break;
    }
}
