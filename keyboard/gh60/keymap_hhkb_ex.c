#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty 
    * ,-----------------------------------------------------------.
    * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
    * |-----------------------------------------------------------|
    * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|
    * |-----------------------------------------------------------|
    * |Contro|  A|  S|  D|  F|  G|  H|  J|  K|  L|Fn1|  '|Enter   |
    * |-----------------------------------------------------------|
    * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Fn0|
    * |-----------------------------------------------------------|
    * |Alt |Gui |Alt |Space                   |Alt |Gui |App |Alt |
    * `-----------------------------------------------------------'
    */
    KEYMAP_MAX(
        ESC,  1,    2,    3,    4,    5,    6,    7,    8,    9,    0,    MINS, EQL,  BSLS, GRV,\
        TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, BSPC,     \
        LCTL, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, NO,   ENT,      \
        LSFT, NO,   Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, FN0,  RSFT,     \
        LALT, LGUI, LALT, SPC,  RALT, RGUI, APP,  RALT),

    /* 1: Cursor(HHKB mode)
     * ,-----------------------------------------------------------.
     * |Pwr| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |Caps |   |   |   |   |   |   |   |Psc|Slk|Pus|Up |   |Backs|
     * |-----------------------------------------------------------|
     * |Contro|VoD|VoU|Mut|   |   |  *|  /|Hom|PgU|Lef|Rig|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |  +|  -|End|PgD|Dow|Shift |   |
     * |-----------------------------------------------------------|
     * |Alt |Gui |Alt |Space                   |Alt |Gui |App |Alt |
     * `-----------------------------------------------------------'
     */
    KEYMAP_MAX(
        PWR,  F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,   F10,  F11,  F12,  INS,  DEL,\
        CAPS, Q,    W,    E,    R,    T,    Y,    U,    PSCR, SLCK, PAUS, UP,   RBRC, BSPC,     \
        LCTL, VOLD,	VOLU, MUTE, F,    G,    PAST, PSLS, HOME, PGUP, LEFT, RGHT, NO,   ENT,      \
        LSFT, NO,   Z,    X,    C,    V,    B,    PPLS, PMNS, END,  PGDN, DOWN, FN0,  RSFT,     \
        LALT, LGUI, LALT, SPC,  RALT, RGUI, APP,  RALT),
};


const uint16_t PROGMEM fn_actions[] = {
    /* HHKB Layout */
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};

