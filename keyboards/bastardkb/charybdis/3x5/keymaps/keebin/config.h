/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#    define DYNAMIC_KEYMAP_LAYER_COUNT 7
#endif // VIA_ENABLE

#ifdef VIAL_ENABLE
/* Vial configuration. Update UID if you distribute multiple boards. */
#    define VIAL_KEYBOARD_UID {0xB1, 0x83, 0x4D, 0xC7, 0x09, 0x5A, 0x2E, 0x61}
#    define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#    define VIAL_UNLOCK_COMBO_COLS {0, 1}
#endif // VIAL_ENABLE

/* Match the ZMK F + left inner Tab Caps Word combo. */
#define CAPS_WORD_COMBO QK_USER_0
#define ARGOS_COMBO_0_KEYS {LSFT_T(KC_F), LT(1, KC_TAB), COMBO_END}
#define ARGOS_COMBO_0_RESULT CAPS_WORD_COMBO
#define ARGOS_COMBO_0_TERM 50
#define COMBO_SHOULD_TRIGGER

#ifndef __arm__
/* Disable unused features. */
#    define NO_ACTION_ONESHOT
#endif // __arm__

#ifdef AUTO_MOUSE_DEFAULT_LAYER
#undef AUTO_MOUSE_DEFAULT_LAYER
#endif
#define AUTO_MOUSE_DEFAULT_LAYER 4

#ifdef LED_DPI_INDICATOR_INDEX
#undef LED_DPI_INDICATOR_INDEX
#endif
#define LED_DPI_INDICATOR_INDEX 0

#ifdef RGBLIGHT_LED_COUNT
#undef RGBLIGHT_LED_COUNT
#endif
#define RGBLIGHT_LED_COUNT 36

/* Invert vertical drag-scroll direction. */
#define BK_POINTING_DEVICE_BK_POINTING_DEVICE_DRAGSCROLL_REVERSE_Y

/* Pointer sensitivity: 300-1000 DPI and 100-300 sniping DPI. */
#define BK_POINTING_DEVICE_MINIMUM_DEFAULT_DPI 300
#define BK_POINTING_DEVICE_DEFAULT_DPI_CONFIG_STEP 100
#define BK_POINTING_DEVICE_DEFAULT_DPI_STEPS 8
#define BK_POINTING_DEVICE_MINIMUM_SNIPING_DPI 100
#define BK_POINTING_DEVICE_SNIPING_DPI_CONFIG_STEP 100
#define BK_POINTING_DEVICE_SNIPING_DPI_STEPS 3

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE
