#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP_ANSI
    (
    	LCTRL,			LSHIFT,		LALT,	LGUI,	RCTRL,		RSHIFT,		RALT,		RGUI,
	    A,				B,			C,		D,		E,			F,			G,			H,
		I,				J,			K,		L,		M,			N,			O,			P,
		Q,				R,			S,		T,		U,			V,			W,			X,
		Y,				Z,			SPACE,	MENU,	COMMA,		DOT,		SLASH,		CAPSLOCK,
		SCOLON,			QUOTE,		ENTER,	TAB,	LBRACKET,	RBRACKET,	BSLASH,		GRAVE,
		1,				2,			3,		4,		5,			6,			7,			8,
		9,				0,			MINUS,	EQUAL,	BSPACE,		NO,			NO,  		NO,
		ESCAPE,			F1,			F2,		F3,		F4,			F5,			F6,			F7,
		F8,				F9,			F10,	F11,	F12,		PSCREEN,	INSERT,		DELETE,
		SCROLLLOCK,		HOME,		END,	PAUSE,	PGUP,		PGDOWN,		NUMLOCK,	KP_SLASH,
		KP_ASTERISK,	KP_MINUS,	KP_7,	KP_8,	KP_9,		KP_4,		KP_5,		KP_6,
		KP_PLUS,		KP_ENTER,	KP_3,	KP_2,	KP_1,		KP_DOT,		KP_0,		RIGHT,
		DOWN,			LEFT,		UP,		NO,		NO,			NO,			NO,			NO
	)
};
const uint16_t PROGMEM fn_actions[] = {
    /* Poker Layout */
    [0] = ACTION_LAYER_MOMENTARY(6),  // to Fn overlay
    [1] = ACTION_LAYER_TOGGLE(4),     // toggle arrow overlay
    [2] = ACTION_LAYER_TOGGLE(5),     // toggle Esc overlay
    [3] = ACTION_MODS_KEY(MOD_RCTL|MOD_RSFT, KC_ESC), // Task(RControl,RShift+Esc)
    [4] = ACTION_LAYER_MOMENTARY(7),  // to Layout selector
    [5] = ACTION_DEFAULT_LAYER_SET(0),  // set qwerty layout
    [6] = ACTION_DEFAULT_LAYER_SET(1),  // set colemak layout
    [7] = ACTION_DEFAULT_LAYER_SET(2),  // set dvorak layout
    [8] = ACTION_DEFAULT_LAYER_SET(3),  // set workman layout
};
