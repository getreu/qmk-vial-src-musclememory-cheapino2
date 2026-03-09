// Copyright 2024 (@getreu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef VIAL_COMBO_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
#include "vial.h"
#include "dynamic_keymap.h"
#endif

/**
 * VIAL-OPTIMIZED KEYMAP FOR CHEAPINO
 *
 * This is a Vial-friendly version based on the musclememory keymap.
 * Tap dance and combos are configured via Vial's dynamic system.
 * Default values are loaded on EEPROM reset via eeconfig_init_user().
 */

/**
 * RGBLIGHT CONFIGURATION & STORAGE
 * Capture and restore dynamic color from EEPROM.
 */
extern rgblight_config_t rgblight_config;

typedef struct {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} custom_hsv_t;

static custom_hsv_t old_color;
static bool initial_capture_done = false;

/**
 * LAYER DEFINITIONS
 */
enum layers {
    _BASE = 0,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5,
    _L6,
    _L7
};

/**
 * COLOR DEFINITIONS
 */
#define COLOR_AMBER     20, 180, 10
#define COLOR_MINT      45, 140, 10
#define COLOR_CYAN      140, 200, 10
#define COLOR_LAVENDER  210, 130, 15
#define COLOR_RED       0, 255, 12
#define COLOR_PINK      230, 170, 10

/**
 * Initialize RGB color capture
 */
void keyboard_post_init_user(void) {
    old_color.h = rgblight_config.hue;
    old_color.s = rgblight_config.sat;
    old_color.v = rgblight_config.val;
    initial_capture_done = true;
}

/**
 * LAYER VISUAL FEEDBACK
 * Changes RGB color based on active layer
 */
layer_state_t layer_state_set_user(layer_state_t state) {
    // Capture color before layer change
    if (!initial_capture_done) {
        old_color.h = rgblight_config.hue;
        old_color.s = rgblight_config.sat;
        old_color.v = rgblight_config.val;
        initial_capture_done = true;
    }

    switch (get_highest_layer(state)) {
        case _L2:
            rgblight_sethsv_noeeprom(COLOR_RED);
            break;
        case _L3:
            rgblight_sethsv_noeeprom(COLOR_CYAN);
            break;
        case _L4:
            rgblight_sethsv_noeeprom(COLOR_LAVENDER);
            break;
        case _L5:
            rgblight_sethsv_noeeprom(COLOR_AMBER);
            break;
        case _L6:
            rgblight_sethsv_noeeprom(COLOR_MINT);
            break;
        case _L7:
            rgblight_sethsv_noeeprom(COLOR_PINK);
            break;
        default:
            // Restore original color on base layer
            rgblight_sethsv_noeeprom(old_color.h, old_color.s, old_color.v);
            break;
    }
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    return state;
}

/**
 * Capture color changes when on base layer
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update saved color when RGB is adjusted on base layer
    if (get_highest_layer(layer_state) == _BASE && record->event.pressed) {
        switch (keycode) {
            case RGB_TOG:
            case RGB_MOD:
            case RGB_RMOD:
            case RGB_HUI:
            case RGB_HUD:
            case RGB_SAI:
            case RGB_SAD:
            case RGB_VAI:
            case RGB_VAD:
                // Wait a bit for the change to apply, then capture
                wait_ms(10);
                old_color.h = rgblight_config.hue;
                old_color.s = rgblight_config.sat;
                old_color.v = rgblight_config.val;
                break;
        }
    }
    return true;
}

/**
 * EEPROM INITIALIZATION - Set Default Combos and Tap Dances
 * This runs when EEPROM is reset (first flash or reset command)
 *
 * Pattern: Set up defaults just like in musclememory, but using Vial's dynamic system.
 * Combos and tap dances will be stored in EEPROM and can be reconfigured via Vial GUI.
 */
#if defined(VIAL_COMBO_ENABLE) || defined(VIAL_TAP_DANCE_ENABLE)
void eeconfig_init_user(void) {
#ifdef VIAL_COMBO_ENABLE
    // Combo 0: Middle thumb keys (Space + Enter) -> Layer 7
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = LGUI_T(KC_SPC);  // Left middle thumb - MUST match keymap exactly
        combo.input[1] = LGUI_T(KC_ENT);  // Right middle thumb - MUST match keymap exactly
        combo.output = MO(_L7);
        dynamic_keymap_set_combo(0, &combo);
    }

    // Combo 1: V + Space -> Layer 7
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = RGUI_T(KC_V);  // MUST match keymap exactly
        combo.input[1] = LGUI_T(KC_SPC);  // MUST match keymap exactly
        combo.output = MO(_L7);
        dynamic_keymap_set_combo(1, &combo);
    }

    // Combo 2: M + Enter -> Layer 7
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = RGUI_T(KC_M);  // MUST match keymap exactly
        combo.input[1] = LGUI_T(KC_ENT);  // MUST match keymap exactly
        combo.output = MO(_L7);
        dynamic_keymap_set_combo(2, &combo);
    }

    // Combo 3: ESC + Backspace -> Toggle Layer 3
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = LT(_L6,KC_ESC);  // MUST match keymap exactly
        combo.input[1] = LT(_L5,KC_BSPC);  // MUST match keymap exactly
        combo.output = TG(_L3);
        dynamic_keymap_set_combo(3, &combo);
    }

    // Combo 4: Q+W+E+T -> Bootloader
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = KC_Q;
        combo.input[1] = KC_W;
        combo.input[2] = KC_E;
        combo.input[3] = KC_T;
        combo.output = QK_BOOT;
        dynamic_keymap_set_combo(4, &combo);
    }

    // Combo 5: Y+I+O+P -> Bootloader
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = KC_Y;
        combo.input[1] = KC_I;
        combo.input[2] = KC_O;
        combo.input[3] = KC_P;
        combo.output = QK_BOOT;
        dynamic_keymap_set_combo(5, &combo);
    }

    // Combo 6: outer thumb keys -> Caps Lock
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = OSL(_L4);         // MUST match keymap exactly
        combo.input[1] = TD(0);            // MUST match keymap exactly
        combo.output = KC_CAPS_LOCK;
        dynamic_keymap_set_combo(6, &combo);
    }

    // Combo 7: outer thumb keys -> Caps Lock
    {
        vial_combo_entry_t combo = {0};
        combo.input[0] = OSL(_L4);         // MUST match keymap exactly
        combo.input[1] = TD(1);            // MUST match keymap exactly
        combo.output = KC_CAPS_LOCK;
        dynamic_keymap_set_combo(7, &combo);
    }

    // Combo 7: Reserved for user customization via Vial GUI
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
    // Tap Dance 0: Right outer thumb - Menu key (matching musclememory behavior)
    // Single tap = KC_APP (context menu), Double tap = Toggle Layer 2
    // Note: Vial's dynamic tap dance cannot implement the layer-aware "clear layers"
    // behavior from musclememory, but provides the core tap/double-tap functionality.
    {
        vial_tap_dance_entry_t td = {0};
        td.on_tap = KC_APP;           // Single tap: Context menu
        td.on_hold = KC_APP;          // Hold: Context menu
        td.on_double_tap = TG(_L2);   // Double tap: Toggle Layer 2
        td.on_tap_hold = KC_NO;       // Ignore
        td.custom_tapping_term = 350; // Match musclememory's 350ms tapping term
        dynamic_keymap_set_tap_dance(0, &td);
    }
    {
        vial_tap_dance_entry_t td = {0};
        td.on_tap = TO(0);            // Single tap: to base layer
        td.on_hold = KC_APP;          // Hold: Context menu
        td.on_double_tap = TG(_L2);   // Double tap: Toggle Layer 2
        td.on_tap_hold = KC_NO;       // Ignore
        td.custom_tapping_term = 350; // Match musclememory's 350ms tapping term
        dynamic_keymap_set_tap_dance(1, &td);
    }
    {
        vial_tap_dance_entry_t td = {0};
        td.on_tap = TO(0);            // Single tap: to base layer
        td.on_hold = MO(_L6);         // Mouse layer
        td.on_double_tap = KC_NO;     // Ingore
        td.on_tap_hold = KC_NO;       // Ignore
        td.custom_tapping_term = 350; // Match musclememory's 350ms tapping term
        dynamic_keymap_set_tap_dance(2, &td);
    }
#endif

    // Reload Vial configuration to activate defaults
    vial_init();
}
#endif

/**
 * KEYMAP DATA
 * Layout for each layer
 *
 * Note: Right outer thumb uses TD(0) - configured in eeconfig_init_user() above
 *       Combos are also configured in eeconfig_init_user() to match musclememory defaults
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_split_3x5_3(
    KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_MUTE,  KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,
    LSFT_T(KC_A), RALT_T(KC_S), LT(_L3,KC_D), LCTL_T(KC_F), LALT_T(KC_G),           LALT_T(KC_H), RCTL_T(KC_J), LT(_L3,KC_K), RALT_T(KC_L), RSFT_T(KC_SCLN),
    KC_Z,         KC_X,         KC_C,         RGUI_T(KC_V), KC_B,                   KC_N,         RGUI_T(KC_M), KC_COMM,      KC_DOT,       KC_SLSH,
    OSL(_L4),     LT(_L6,KC_ESC), LGUI_T(KC_SPC),                                   LGUI_T(KC_ENT), LT(_L5,KC_BSPC), TD(0)
),

[_L1] = LAYOUT_split_3x5_3(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                     KC_TRNS, KC_TRNS, KC_TRNS
),

[_L2] = LAYOUT_split_3x5_3(
    KC_U,    KC_D,    KC_E,             KC_F,    KC_N,    KC_TRNS, KC_PMNS, KC_P7,   KC_P8,         KC_P9,   KC_P0,
    KC_PSLS, KC_PAST, LT(_L3,KC_PEQL),  KC_TAB,  KC_BSPC,          KC_NUM,  KC_P4,   LT(_L3,KC_P5), KC_P6,   KC_PENT,
    KC_X,    KC_A,    KC_B,             KC_C,    LSFT(KC_SCLN),    KC_PPLS, KC_P1,   KC_P2,         KC_P3,   KC_PDOT,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L3] = LAYOUT_split_3x5_3(
    KC_1,           KC_2,           KC_3,             KC_4,           KC_5,           KC_TRNS, KC_6,            KC_7,            KC_8,          KC_9,            KC_0,
    LSFT_T(KC_ESC), RALT_T(KC_INS), LT(_L3,KC_DEL),   LCTL_T(KC_TAB), LALT_T(KC_BSPC),         LALT_T(KC_LEFT), RCTL_T(KC_DOWN), LT(_L3,KC_UP), RALT_T(KC_RGHT), RSFT_T(KC_ENT),
    KC_GRV,         KC_MINS,        KC_EQL,           RGUI_T(KC_LBRC), KC_RBRC,                KC_BSLS,         RGUI_T(KC_QUOT), KC_COMM,       KC_DOT,          KC_SLSH,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L4] = LAYOUT_split_3x5_3(
    KC_F1,          KC_F2,          KC_F3,   KC_F4,           KC_F5,   KC_TRNS, KC_F6,    KC_F7,   KC_F8,   KC_F9,          KC_F10,
    LSFT_T(KC_F11), RALT_T(KC_F12), KC_F13,  LCTL_T(KC_F14),  KC_F15,           KC_F16,   KC_F17,  KC_F18,  RALT_T(KC_F19), RSFT_T(KC_F20),
    KC_F21,         KC_F22,         KC_F23,  RGUI_T(KC_F24),  KC_NO,            KC_NO,    KC_NO,   KC_NO,   KC_NO,          KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L5] = LAYOUT_split_3x5_3(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_HOME, KC_DEL,  KC_INS,  KC_END,  KC_BSPC,
    KC_ESC,  KC_INS,  KC_DEL,  KC_TAB,  KC_BSPC,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_PGDN, KC_PGUP, KC_NO,   KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L6] = LAYOUT_split_3x5_3(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    MS_BTN5, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4,          MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, MS_BTN1,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L7] = LAYOUT_split_3x5_3(
    QK_CLEAR_EEPROM,   KC_NO,   RGB_VAD, RGB_VAI, RGB_TOG, KC_TRNS, KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,
    KC_NO,   KC_NO,   RGB_HUD, RGB_HUI, RGB_MOD,          KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,
    KC_NO,   KC_NO,   RGB_SAD, RGB_SAI, RGB_RMOD,         KC_MPLY, KC_MPRV, KC_MNXT, KC_NO,   KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
)

};
