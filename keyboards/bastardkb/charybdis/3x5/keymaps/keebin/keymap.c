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
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_BUTTON,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
// Matches ZMK Corne left thumb 3, repurposed: LT(FUNCTION, TAB) instead of
// LT(MOUSE, TAB), since Mouse/Pointer now lives on the DOT key (see below).
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
// Matches ZMK Corne bottom pinkies: u_lt U_BUTTON Z / SLASH. NOTE: unlike the
// Corne, only the left pinky (Z) triggers Button here; the right pinky (SLSH)
// is a plain key, and DOT triggers the Pointer/Mouse layer instead (avoids
// relying on the weaker right pinky for a frequently-used layer).
#define _L_BTN(KC) LT(LAYER_BUTTON, KC)
#define DOT_MOU LT(LAYER_BUTTON, KC_DOT)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
       KC_Z,    KC_X,    KC_C, KC_V,    KC_B,    KC_N,    KC_M, KC_COMM, DOT_MOU, KC_SLSH, \
                      ESC_MED, SPC_NAV, TAB_FUN, ENT_SYM, BSP_NUM

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI

/*
 * Layers used on the Charybdis Nano.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
// F-keys on the left half, GACS mods + bootloader on the right half, matching
// the Corne's FUN layer column order.
#define LAYOUT_LAYER_FUNCTION                                                                 \
      KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, \
      KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL, ______________HOME_ROW_GACS_R______________, \
      KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX,  KC_RALT, XXXXXXX, \
                      XXXXXXX, QK_BOOT, _______, XXXXXXX, XXXXXXX

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
#define LAYOUT_LAYER_MEDIA                                                                    \
    XXXXXXX,RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX, XXXXXXX,RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX, \
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, \
    XXXXXXX, XXXXXXX, XXXXXXX,  EE_CLR, QK_BOOT, QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, \
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY

/**
 * \brief Combined Button + Pointer layer.
 *
 * Left hand keeps Button-layer behavior (clipboard + F13-F17) while the right
 * hand top/bottom rows are repurposed for pointer behavior controls.
 */
#define LAYOUT_LAYER_BUTTON                                                                   \
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Y), S_D_MOD, S_D_RMOD, DPI_MOD, DPI_RMOD, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
      XXXXXXX,    XXXXXXX,    DRGSCRL,    SNIPING,    XXXXXXX, XXXXXXX, SNP_TOG, DRG_TOG, XXXXXXX, XXXXXXX, \
                      MS_BTN3, MS_BTN1, MS_BTN2, MS_BTN2, MS_BTN1

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
// Clipboard ops (undo/cut/copy/paste/redo) on the top and bottom rows,
// arrows + caps lock on the home row, matching the Corne's NAV layer.
#define LAYOUT_LAYER_NAVIGATION                                                               \
    _______________DEAD_HALF_ROW_______________, LCTL(KC_Y), LCTL(KC_V), LCTL(KC_C), LCTL(KC_X), LCTL(KC_Z), \
    ______________HOME_ROW_GACS_L______________, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_CAPS, \
    LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_Y), KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, \
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
// Numpad on the left half, brackets/operators (with home-row mods) on the
// right half, matching the Corne's NUM layer.
#define LAYOUT_LAYER_NUMERAL                                                                  \
    KC_PERC,    KC_7,    KC_8,    KC_9,  KC_AT, XXXXXXX, KC_LBRC, KC_RBRC, KC_ASTR, QK_BOOT, \
     KC_GRV,    KC_4,    KC_5,    KC_6, KC_ASTR, XXXXXXX, RSFT_T(KC_UNDS), RCTL_T(KC_EQL), RALT_T(KC_LPRN), RGUI_T(KC_RPRN), \
    KC_COLN,    KC_1,    KC_2,    KC_3, KC_PIPE, XXXXXXX, KC_MINS, KC_PLUS, KC_CIRC, KC_BSLS, \
                       KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
// $, braces, brackets on the left half, GACS mods on the right home row,
// matching the Corne's SYM layer.
#define LAYOUT_LAYER_SYMBOLS                                                                  \
     KC_DLR, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, \
    KC_TILD,  KC_EQL, KC_MINS, KC_PLUS, KC_AMPR, ______________HOME_ROW_GACS_R______________, \
    KC_SCLN, KC_EXLM, KC_HASH, KC_CIRC, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX,  KC_RALT, XXXXXXX, \
                      KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * \brief Add button layer key to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * Only wraps the left pinky (L20) with the Button layer-tap; the right pinky
 * (R29) is left untouched as a plain key.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     BUTTON_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _BUTTON_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_BTN(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,         R29,  \
      __VA_ARGS__
#define BUTTON_MOD(...) _BUTTON_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    BUTTON_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_BUTTON] = LAYOUT_wrapper(LAYOUT_LAYER_BUTTON),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
};

// clang-format on