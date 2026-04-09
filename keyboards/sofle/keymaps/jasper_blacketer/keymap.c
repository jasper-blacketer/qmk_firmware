// Copyright 2024 Jasper Blacketer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum sofle_layers {
    _BASE,
    _SYMBOLS,
    _NAV,
    _SPECIAL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |` /L3 |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   =  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Tab/L2|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | MO1  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |' /L1 |
 * |------+------+------+------+------+------|  MUTE |    | Esc   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCtl | LAlt | LGui | Bspc | /Delete /       \Enter \  |Space | RGui | RAlt | RCtl |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_BASE] = LAYOUT(
  LT(_SPECIAL,KC_GRV), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  LT(_NAV,KC_TAB),     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  MO(_SYMBOLS),        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT(_SYMBOLS,KC_QUOT),
  KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_MUTE,                KC_ESC, KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
              KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, KC_DEL,         KC_ENT, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
),

/* SYMBOLS - F-keys, symbols left / numpad right
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   &  |                    |   |  |   7  |   8  |   9  |   *  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   #  |   $  |   (  |   )  |   *  |-------.    ,-------|  KP/ |   4  |   5  |   6  |   +  |   '  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   %  |   ^  |   [  |   ]  |   ~  |-------|    |-------|   \  |   1  |   2  |   3  |  KP/ |KPEnt |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | KP=  |      |      |      | /       /       \   _  \  |   -  |   0  | KP.  | KP-  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_SYMBOLS] = LAYOUT(
  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,
  XXXXXXX, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_AMPR,           KC_PIPE, KC_P7,   KC_P8,   KC_P9,   KC_PAST,   KC_F12,
  XXXXXXX, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_ASTR,           KC_PSLS, KC_P4,   KC_P5,   KC_P6,   S(KC_EQL), KC_QUOT,
  XXXXXXX, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, XXXXXXX,  XXXXXXX, KC_BSLS, KC_P1,   KC_P2,   KC_P3,     KC_PSLS, KC_PENT,
                    KC_PEQL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  S(KC_MINS), KC_MINS, KC_0,  KC_PDOT, KC_PMNS
),

/* NAV - hold Tab for navigation / toggle encoder for FPS gaming
 * Left (gaming):  Esc+num row remapped, WASD on home row, modifiers on bottom
 * Right (nav):    Arrows, Page/Home/End, scroll wheel
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Esc  |   5  |   1  |   2  |   3  |   4  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | Tab  |   Q  |   W  |   E  |   R  |                    |WhlUp | PgUp |  Up  | Home |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   A  |   S  |   D  |   F  |-------.    ,-------|MBtn5 | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|TG(NAV)|    |       |------+------+------+------+------+------|
 * | LCtl |LShift|   Z  |   X  |   C  |   V  |-------|    |-------|WhlDn | PgDn | Down | End  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |   G  | /Space  /       \ Ins  \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *             `----------------------------------'           '------''---------------------------'
 */
[_NAV] = LAYOUT(
  KC_ESC,  KC_5,    KC_1,    KC_2,    KC_3,    KC_4,              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
  KC_TAB,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,              KC_WH_U, KC_PGUP, KC_UP,   KC_HOME, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,              KC_BTN5, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
  KC_LCTL, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    TG(_NAV), XXXXXXX, KC_WH_D, KC_PGDN, KC_DOWN, KC_END,  XXXXXXX, XXXXXXX,
                    XXXXXXX, XXXXXXX, XXXXXXX, KC_G,    KC_SPC,   KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* SPECIAL - accessed by holding ` (grave)
 * ` + 5       = Alt+F4
 * ` + encoder = toggle NAV/FPS layern
 */
[_SPECIAL] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LALT(KC_F4),       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_NAV),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

};

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };
    oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:    oled_write_P(PSTR("Base\n"), false);   break;
        case _SYMBOLS: oled_write_P(PSTR("Symbl"), false);    break;
        case _NAV:     oled_write_P(PSTR("Nav\n"), false);    break;
        case _SPECIAL: oled_write_P(PSTR("Spec\n"), false);   break;
        default:       oled_write_ln_P(PSTR("Undef"), false); break;
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        render_logo();
    }
    return false;
}

#endif
