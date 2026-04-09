---
name: sofle-qmk
description: Guides creating and modifying custom QMK firmware keymaps for the Sofle split keyboard (rev1). Use when the user wants to create a new keymap, modify layers, configure encoders, customize OLED displays, set up RGB lighting, or flash firmware for a Sofle keyboard.
---

# Sofle QMK Keymap

## Quick start

New keymap goes in `keyboards/sofle/keymaps/<your_name>/` with three files:

```
keymap.c   # layers and callbacks
config.h   # keymap-level overrides only
rules.mk   # feature flags
```

Minimal `keymap.c`:
```c
// Copyright 2024 Your Name
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum sofle_layers { _BASE, _SYM };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( /* 58 keys — see REFERENCE.md for layout */ ),
    [_SYM]  = LAYOUT( /* ... */ ),
};
```

## Build & flash

```bash
qmk compile -kb sofle/rev1 -km <your_name>
qmk flash   -kb sofle/rev1 -km <your_name>
qmk lint    -kb sofle/rev1 -km <your_name>
```

## Key patterns

| Pattern | Example | Use for |
|---|---|---|
| Momentary layer | `MO(_SYM)` | Hold for layer |
| Layer-tap | `LT(_NAV, KC_TAB)` | Tap=key, hold=layer |
| Tri Layer | `TL_LOWR` / `TL_UPPR` | Both held = 3rd layer |
| Toggle layer | `TG(_NAV)` | Sticky layer toggle |

**Tri Layer** (`rules.mk`: `TRI_LAYER_ENABLE = yes`): holding lower+upper activates adjust. No extra config needed — `TL_LOWR`/`TL_UPPR` keycodes do it automatically.

## Custom keycodes

```c
enum custom_keycodes { MY_KEY = QK_USER, MY_KEY2 };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_KEY:
            if (record->event.pressed) { /* press */ }
            else { /* release */ }
            return false;
    }
    return true;
}
```

## rules.mk feature flags

```makefile
WPM_ENABLE = yes          # words-per-minute counter
TRI_LAYER_ENABLE = yes    # tri-layer (lower+upper=adjust)
ENCODER_MAP_ENABLE = yes  # declarative encoder map (preferred)
```

## Advanced features

See [REFERENCE.md](REFERENCE.md) for:
- Encoder callbacks and ENCODER_MAP
- OLED display (layer name, WPM, caps lock)
- RGB matrix and rgblight control
- config.h override options
- Layout grid (which key is which position)
