# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## About This Fork

This is a personal fork of [QMK Firmware](https://github.com/qmk/qmk_firmware) containing a custom keymap for the **Sofle** split keyboard at `keyboards/sofle/keymaps/jasper_blacketer/`. The primary development work in this repo is on that keymap.

## Build & Flash Commands

```bash
# Compile the Jasper Blacketer Sofle keymap
qmk compile -kb sofle/rev1 -km jasper_blacketer

# Compile and flash directly
qmk flash -kb sofle/rev1 -km jasper_blacketer

# Lint the keymap
qmk lint -kb sofle/rev1 -km jasper_blacketer

# Format JSON config files (run before submitting any keyboard PRs)
qmk format-json -i keyboards/sofle/info.json

# Format C code
qmk format-c keyboards/sofle/keymaps/jasper_blacketer/keymap.c
```

## Keymap Architecture (`keyboards/sofle/keymaps/jasper_blacketer/`)

**5 layers** defined in `keymap.c`:
- `_QWERTY` (0) — base layer; CapsLock-style hold on left home row activates `_SYMBOLS`; Tab hold activates `_CURSOR`
- `_SYMBOLS` (1) — symbols, F-keys, numpad on right half
- `_CURSOR` (2) — navigation (arrows, page up/down, word jump, home/line end)
- `_SPECIAL` / `_ADJUST` (3) — bootloader, media, OS/mode switching (accessed via Tri Layer)
- `_FPS` (4) — gaming layer

**Tri Layer** (`rules.mk`: `TRI_LAYER_ENABLE = yes`): holding both `_SYMBOLS` and `_CURSOR` activates `_SPECIAL`. Configured in `config.h`.

**Custom keycodes** (`KC_PRVWD`, `KC_NXTWD`, `KC_LSTRT`, `KC_LEND`): word/line navigation that adapts between Mac (GUI+arrow) and Windows/Linux (Ctrl+arrow) using `keymap_config.swap_lctl_lgui`.

**Mac/Win toggle**: `CG_TOGG` on the Adjust layer swaps Ctrl and GUI globally; navigation custom keycodes detect this and adjust behavior accordingly.

## QMK Code Conventions

- License header required on all `.c` and `.h` files: `// Copyright YEAR Name (@github) / // SPDX-License-Identifier: GPL-2.0-or-later`
- Use `#pragma once` not `#ifndef` guards in headers
- Use `#include QMK_KEYBOARD_H` (not board-specific includes) in keymaps
- Layer enums preferred over `#define`s for layer numbers
- Custom keycodes must start with `QK_USER` as first entry
- Use `wait_ms()` not `_delay_ms()`; use `timer_read()` from `timer.h`
- No direct GPIO/I2C/SPI register access — use QMK abstractions

## Keyboard-level vs Keymap-level config

- `keyboards/sofle/info.json` — hardware config (pins, matrix, USB VID, features, OLED, encoders)
- `keyboards/sofle/rev1/keyboard.json` — rev1 variant specifics
- `keyboards/sofle/keymaps/jasper_blacketer/config.h` — keymap-level overrides only (Tri Layer settings)
- `keyboards/sofle/keymaps/jasper_blacketer/rules.mk` — keymap feature flags (`TRI_LAYER_ENABLE`)

Do **not** put user-preference defines in keyboard-level `config.h`. Do not re-define defaults (like `DEBOUNCE`).

## PR Branch Targeting (upstream QMK)

When contributing back to upstream QMK:
- New keyboards → `master`
- Everything else (updates, refactors, core changes) → `develop`
- Never submit from your own `master` branch; use feature branches
