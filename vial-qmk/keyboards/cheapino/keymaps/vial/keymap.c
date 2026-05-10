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
// Define a custom structure to group HSV values
typedef struct {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} custom_hsv_t;
static custom_hsv_t old_color;

/**
 * LAYER DEFINITIONS
 */
enum layers { _BASE = 0, _L1, _L2, _L3, _L4, _L5, _L6, _L7 };

/**
 * COLOR DEFINITIONS
 */
#define COLOR_AMBER     20, 180, 10
#define COLOR_MINT      45, 140, 10
#define COLOR_CYAN      140, 200, 10
#define COLOR_LAVENDER  210, 130, 15
#define COLOR_RED       0, 255, 12
#define COLOR_PINK      230, 170, 10
#define COLOR_WHITE     0, 0, 10

/**
 * Initialize RGB color capture
 */
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

/**
 * LAYER VISUAL FEEDBACK
 * Changes RGB color based on active layer
 */
layer_state_t layer_state_set_user(layer_state_t state) {
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
    return state;
}

/**
 * Capture color changes when on base layer
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update saved color when RGB is adjusted
    if (record->event.pressed) {
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
                old_color.h = rgblight_get_hue();
                old_color.s = rgblight_get_sat();
                old_color.v = rgblight_get_val();
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
/**
 * EEPROM INITIALIZATION - Full Vial & RGB Integration
 * This runs when EEPROM is reset to load your screenshot defaults.
 */
#if defined(VIAL_COMBO_ENABLE) || defined(VIAL_TAP_DANCE_ENABLE)
void eeconfig_init_user(void) {

#ifdef VIAL_COMBO_ENABLE
    // 2. Load Dynamic Combos (These write to EEPROM)
    vial_combo_entry_t combo = {0};

    // Combo 0: Space + Enter -> Layer 7
    combo.input[0] = LGUI_T(KC_SPC);
    combo.input[1] = LGUI_T(KC_ENT);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(0, &combo);

    // Combo 1: V + Space -> Layer 7
    combo.input[0] = RGUI_T(KC_V);
    combo.input[1] = LGUI_T(KC_SPC);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(1, &combo);

    // Combo 2: M + Enter -> Layer 7
    combo.input[0] = RGUI_T(KC_M);
    combo.input[1] = LGUI_T(KC_ENT);
    combo.output = MO(_L7);
    dynamic_keymap_set_combo(2, &combo);

    // Combo 3: ESC + Backspace -> Toggle Layer 3
    combo.input[0] = LT(_L6, KC_ESC);
    combo.input[1] = LT(_L5, KC_BSPC);
    combo.output = TG(_L3);
    dynamic_keymap_set_combo(3, &combo);

    // Combo 4 & 5: Outer thumbs -> Caps Lock
    combo.input[0] = OSL(_L4); combo.input[1] = TD(0);
    combo.output = KC_CAPS_LOCK;
    dynamic_keymap_set_combo(4, &combo);

    combo.input[0] = OSL(_L4); combo.input[1] = TD(1);
    combo.output = KC_CAPS_LOCK;
    dynamic_keymap_set_combo(5, &combo);

    // Combo 6: Q+W+E+T -> Bootloader
    combo.input[0] = KC_Q; combo.input[1] = KC_W; combo.input[2] = KC_E; combo.input[3] = KC_T;
    combo.output = QK_BOOT;
    dynamic_keymap_set_combo(6, &combo);

    // Combo 7: Y+I+O+P -> Bootloader
    combo.input[0] = KC_Y; combo.input[1] = KC_I; combo.input[2] = KC_O; combo.input[3] = KC_P;
    combo.output = QK_BOOT;
    dynamic_keymap_set_combo(7, &combo);

#endif

#ifdef VIAL_TAP_DANCE_ENABLE
    // 4. Load Dynamic Tap Dances
    vial_tap_dance_entry_t td = {0};

    // TD 0: APP / TG(_L2)
    td.on_tap = KC_APP; td.on_hold = KC_APP; td.on_double_tap = TG(_L2);
    td.custom_tapping_term = 350;
    dynamic_keymap_set_tap_dance(0, &td);

    // TD 1: TO(0) / TG(_L2)
    td.on_tap = TO(0); td.on_hold = KC_APP; td.on_double_tap = TG(_L2);
    td.custom_tapping_term = 350;
    dynamic_keymap_set_tap_dance(1, &td);

    // TD 2: TO(0) / MO(_L6)
    td.on_tap = TO(0); td.on_hold = MO(_L6); td.on_double_tap = KC_NO;
    td.custom_tapping_term = 350;
    dynamic_keymap_set_tap_dance(2, &td);
#endif

    // Finalize the sync
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
    KC_NO,          KC_NO,          KC_NO,           KC_PEQL,        KC_PAST, KC_TRNS, KC_KP_PLUS,          KC_KP_7,         KC_KP_8,          KC_KP_9,         KC_KP_0,
    LSFT_T(KC_ESC), RALT_T(KC_INS), LT(_L3, KC_DEL), LCTL_T(KC_TAB), LALT_T(KC_BSPC),  LALT_T(KC_NUM_LOCK), RCTL_T(KC_KP_4), LT(_L3, KC_KP_5), RALT_T(KC_KP_6), RSFT_T(KC_PENT),
    KC_NO,          KC_NO,          KC_NO,           RGUI_T(KC_NO),  KC_PSLS,          KC_KP_MINUS,         RGUI_T(KC_KP_1), KC_KP_2,          KC_KP_3,         KC_KP_DOT,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L3] = LAYOUT_split_3x5_3(
    KC_1,           KC_2,           KC_3,             KC_4,           KC_5,  KC_TRNS,  KC_6,            KC_7,            KC_8,          KC_9,            KC_0,
    LSFT_T(KC_ESC), RALT_T(KC_INS), LT(_L3,KC_DEL),   LCTL_T(KC_TAB), LALT_T(KC_BSPC), LALT_T(KC_LEFT), RCTL_T(KC_DOWN), LT(_L3,KC_UP), RALT_T(KC_RGHT), RSFT_T(KC_ENT),
    KC_GRV,         KC_MINS,        KC_EQL,           RGUI_T(KC_LBRC), KC_RBRC,        KC_BSLS,         RGUI_T(KC_QUOT), KC_COMM,       KC_DOT,          KC_SLSH,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L4] = LAYOUT_split_3x5_3(
    KC_F1,          KC_F2,          KC_F3,   KC_F4,           KC_F5,   QK_REBOOT, KC_F6,          KC_F7,          KC_F8,   KC_F9,          KC_F10,
    LSFT_T(KC_F11), RALT_T(KC_F12), KC_F13,  LCTL_T(KC_F14),  LALT_T(KC_F15),     LALT_T(KC_F16), RCTL_T(KC_F17), KC_F18,  RALT_T(KC_F19), RSFT_T(KC_F20),
    KC_F21,         KC_F22,         KC_F23,  RGUI_T(KC_F24),  KC_NO,              KC_NO,          RGUI_T(KC_NO),  KC_NO,   KC_NO,          KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L5] = LAYOUT_split_3x5_3(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  QK_CLEAR_EEPROM,  KC_HOME, KC_DEL,  KC_INS,  KC_END,  KC_BSPC,
    KC_ESC,  KC_INS,  KC_DEL,  KC_TAB,  KC_BSPC,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_PGDN, KC_PGUP, KC_NO,   KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L6] = LAYOUT_split_3x5_3(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  QK_BOOT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    MS_BTN5, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4,          MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, MS_BTN1,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
),

[_L7] = LAYOUT_split_3x5_3(
    QK_CLEAR_EEPROM, KC_NO, RGB_VAD, RGB_VAI, RGB_TOG, KC_NO, KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,
    QK_BOOT,         KC_NO, RGB_HUD, RGB_HUI, KC_NO,          KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,
    QK_REBOOT, KC_NO,   RGB_SAD, RGB_SAI, KC_NO,           KC_MPLY, KC_MPRV, KC_MNXT, KC_NO,   KC_NO,
    KC_TRNS, TD(2), KC_TRNS,                              KC_TRNS, KC_TRNS, TD(1)
)
};
