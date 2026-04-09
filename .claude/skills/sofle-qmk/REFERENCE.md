# Sofle QMK Reference

## Layout positions

The Sofle `LAYOUT` macro takes **58 keys** in this order:

```
Left half (top-to-bottom, left-to-right):
  Row 0: col0–col5   (6 keys, number row)
  Row 1: col0–col5   (6 keys)
  Row 2: col0–col5   (6 keys)
  Row 3: col0–col5 + encoder_btn  (7 keys)
  Row 4: col0–col4   (5 keys, thumb cluster)

Right half mirrors left (same order).
```

The encoder button sits between rows 3 left and 3 right in the macro args.

Visual reference from jasper_blacketer:
```
[_BASE] = LAYOUT(
  LT(_SPECIAL,KC_GRV), KC_1, KC_2, KC_3, KC_4, KC_5,          KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
  LT(_NAV,KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,              KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
  MO(_SYMBOLS), KC_A, KC_S, KC_D, KC_F, KC_G,                  KC_H, KC_J, KC_K, KC_L, KC_SCLN, LT(_SYMBOLS,KC_QUOT),
  KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE,   XXXXXXX, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                KC_LCTL, KC_LALT, KC_LGUI, KC_BSPC, KC_DEL,   KC_ENT, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL
)
```

---

## Encoders

The Sofle rev1 has **one rotary encoder per half** (left: F5/F4, right: F4/F5).

### Callback style (add to keymap.c):
```c
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {          // left encoder
        tap_code(clockwise ? KC_VOLU : KC_VOLD);
    } else if (index == 1) {   // right encoder
        tap_code(clockwise ? KC_PGDN : KC_PGUP);
    }
    return false;
}
```

### Declarative map style (preferred, `rules.mk`: `ENCODER_MAP_ENABLE = yes`):
```c
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_SYMBOLS] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
};
#endif
```

---

## OLED Display

The Sofle has a **128×32 OLED on each half**. The keyboard-level code rotates the master OLED to 270° (vertical strip). Enable with `OLED_ENABLE = yes` in `rules.mk` (already on by default in `info.json`).

```c
#ifdef OLED_ENABLE

// Called once at init — return desired rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;  // vertical on master
}

// Render loop — return false to suppress keyboard-level rendering
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // master side: show layer + caps lock
        oled_write_P(PSTR("LYR: "), false);
        switch (get_highest_layer(layer_state)) {
            case _BASE:    oled_write_P(PSTR("Base\n"), false); break;
            case _SYMBOLS: oled_write_P(PSTR("Sym\n"),  false); break;
            default:       oled_write_P(PSTR("???\n"),  false); break;
        }
        led_t leds = host_keyboard_led_state();
        oled_write_P(PSTR("CAPS"), leds.caps_lock);
    } else {
        // secondary side: show WPM (needs SPLIT_WPM_ENABLE in config.h + WPM_ENABLE in rules.mk)
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);
    }
    return false;
}

#endif
```

**config.h** for split WPM:
```c
#define SPLIT_WPM_ENABLE
```

---

## RGB Lighting

The Sofle has **72 WS2812 LEDs** (36 per half) on the `D3` pin. Two drivers are available — pick one:

### rgblight (per-key or underglow solid/effects)
Already enabled in `info.json`. In `rules.mk`: nothing needed (it's on).

Control in keymap:
```c
// In process_record_user or layer_state_set_user:
rgblight_sethsv(HSV_RED);      // set color
rgblight_mode(RGBLIGHT_MODE_BREATHING + 3);
rgblight_toggle();
```

### rgb_matrix (per-key addressing, more powerful)
`info.json` already maps all 72 LEDs. In `rules.mk`:
```makefile
RGB_MATRIX_ENABLE = yes
```

Layer-based color example:
```c
bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _SYMBOLS:
            rgb_matrix_set_color_all(RGB_BLUE);
            break;
        case _NAV:
            rgb_matrix_set_color_all(RGB_GREEN);
            break;
    }
    return false;
}
```

HSV color constants: `HSV_RED`, `HSV_GREEN`, `HSV_BLUE`, `HSV_ORANGE`, `HSV_PURPLE`, `HSV_CYAN`, `HSV_WHITE`, `HSV_OFF`

---

## config.h overrides (keymap-level only)

```c
#pragma once

// Tapping
#define TAPPING_TERM 200          // ms to distinguish tap vs hold
#define PERMISSIVE_HOLD           // rolling keys treated as hold sooner

// Tri Layer (if TRI_LAYER_ENABLE = yes in rules.mk)
#define TRI_LAYER_LOWER_LAYER  1
#define TRI_LAYER_UPPER_LAYER  2
#define TRI_LAYER_ADJUST_LAYER 3

// Split sync
#define SPLIT_WPM_ENABLE          // sync WPM to secondary half

// RGB sleep (already in info.json, but can override)
// #define RGBLIGHT_SLEEP
```

Do **not** redefine defaults like `DEBOUNCE`. Do not put user defines in keyboard-level `config.h`.

---

## Mac/Win toggle pattern

`CG_TOGG` swaps Ctrl↔GUI globally. Detect in custom keycodes:
```c
if (keymap_config.swap_lctl_lgui) {
    // Mac behavior: use GUI/Cmd
    register_mods(mod_config(MOD_LGUI));
} else {
    // Win/Linux behavior: use Ctrl
    register_mods(mod_config(MOD_LCTL));
}
```
