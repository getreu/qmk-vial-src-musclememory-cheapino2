#include QMK_KEYBOARD_H

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
 *
 * TAP DANCE DEFINITION
 *
 */
// - Base Layer: Single Tap = KC_APP | Hold = Activate L2 momentarily | Double Tap = Toggle L2
// - Other Layers: Any interaction = layer_clear() (Reset to Base)
enum { TD_CMENU };

void td_cmenu_finished(tap_dance_state_t *state, void *user_data) {
    if (get_highest_layer(layer_state) == _BASE) {
        if (state->pressed) {
            // Hold = Momentarily activate L2
            layer_on(_L2);
        } else {
            // Tapped
            if (state->count == 1) {
                tap_code16(KC_APP);
            } else if (state->count >= 2) {
                layer_invert(_L2);
            }
        }
    } else {
        // If we are on ANY other layer, reset everything to Base
        layer_clear();
    }
}

void td_cmenu_reset(tap_dance_state_t *state, void *user_data) {
    // Only deactivate if count=1 AND we're on L2
    // (count=1 & on L2 means it was a hold, not a toggle)
    if (state->count == 1 && get_highest_layer(layer_state) == _L2) {
        layer_off(_L2);
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CMENU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_cmenu_finished, td_cmenu_reset)
};

// PER-KEY TAPPING TERM
// Dynamically adjusts the tapping term.
// Uses the global TAPPING_TERM from keyboard.json/config.h as the baseline.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Relaxed window for the TD_4 tap dance (Menu/Layer 2 Toggle)
        case TD(TD_CMENU):
            return 350;

        // Slightly more buffer for thumb-based layer taps (optional)
        case LT(_L6, KC_ESC):
        case MT(MOD_LGUI, KC_SPC):
        case MT(MOD_LGUI, KC_ENT):
        case LT(_L5, KC_BSPC):
            return 250;

        // Fallback to the default value defined in keyboard.json or config.h
        default:
            return 200;
    }
}


/**
 *
 * POST-PROCESSING: post_process_record_user
 * Logic that runs AFTER a key press is handled.
 * Specifically used to clear layers (return to base) after a Tap-Hold key is tapped.
 *
 */
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed && record->tap.count > 0) {
        switch (keycode) {
            case LT(_L6, KC_NO):
                layer_clear(); // Reset to Base Layer
                break;
        }
    }
}

/**
 * KEYMAP DATA
 * The matrix definition for each layer.
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MUTE, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    LSFT_T(KC_A), RALT_T(KC_S), LT(_L3, KC_D), LCTL_T(KC_F), LALT_T(KC_G), LALT_T(KC_H), RCTL_T(KC_J), LT(_L3, KC_K), RALT_T(KC_L), RSFT_T(KC_SCLN),
    KC_Z,    KC_X,    KC_C,    RGUI_T(KC_V), KC_B,    KC_N,    RGUI_T(KC_M), KC_COMM, KC_DOT,  KC_SLSH,
    OSL(_L4), LT(_L6, KC_ESC), MT(MOD_LGUI, KC_SPC), MT(MOD_LGUI, KC_ENT), LT(_L5, KC_BSPC), TD(TD_CMENU)
),

[_L1] = LAYOUT_split_3x5_3(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
),

[_L2] = LAYOUT_split_3x5_3(
    KC_NO,          KC_NO,          KC_NO,           KC_PEQL,        KC_PAST, KC_TRNS, KC_KP_PLUS,          KC_KP_7,         KC_KP_8,          KC_KP_9,         KC_KP_0,
    LSFT_T(KC_ESC), RALT_T(KC_INS), LT(_L3, KC_DEL), LCTL_T(KC_TAB), LALT_T(KC_BSPC),  LALT_T(KC_NUM_LOCK), RCTL_T(KC_KP_4), LT(_L3, KC_KP_5), RALT_T(KC_KP_6), RSFT_T(KC_PENT),
    KC_NO,          KC_NO,          KC_NO,           RGUI_T(KC_NO),  KC_PSLS,          KC_KP_MINUS,         RGUI_T(KC_KP_1), KC_KP_2,          KC_KP_3,         KC_KP_DOT,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
),

[_L3] = LAYOUT_split_3x5_3(
    KC_1,           KC_2,           KC_3,             KC_4,           KC_5,  KC_TRNS,  KC_6,            KC_7,            KC_8,          KC_9,            KC_0,
    LSFT_T(KC_ESC), RALT_T(KC_INS), LT(_L3,KC_DEL),   LCTL_T(KC_TAB), LALT_T(KC_BSPC), LALT_T(KC_LEFT), RCTL_T(KC_DOWN), LT(_L3,KC_UP), RALT_T(KC_RGHT), RSFT_T(KC_ENT),
    KC_GRV,         KC_MINS,        KC_EQL,           RGUI_T(KC_LBRC), KC_RBRC,        KC_BSLS,         RGUI_T(KC_QUOT), KC_COMM,       KC_DOT,          KC_SLSH,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
),

[_L4] = LAYOUT_split_3x5_3(
    KC_F1,          KC_F2,          KC_F3,   KC_F4,           KC_F5,   QK_REBOOT, KC_F6,          KC_F7,          KC_F8,   KC_F9,          KC_F10,
    LSFT_T(KC_F11), RALT_T(KC_F12), KC_F13,  LCTL_T(KC_F14),  LALT_T(KC_F15),     LALT_T(KC_F16), RCTL_T(KC_F17), KC_F18,  RALT_T(KC_F19), RSFT_T(KC_F20),
    KC_F21,         KC_F22,         KC_F23,  RGUI_T(KC_F24),  KC_NO,              KC_NO,          RGUI_T(KC_NO),  KC_NO,   KC_NO,          KC_NO,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
),

[_L5] = LAYOUT_split_3x5_3(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  QK_CLEAR_EEPROM,  KC_HOME, KC_DEL,  KC_INS,  KC_END,  KC_BSPC,
    KC_ESC,  KC_INS,  KC_DEL,  KC_TAB,  KC_BSPC,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_PGDN, KC_PGUP, KC_NO,   KC_NO,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
),

[_L6] = LAYOUT_split_3x5_3(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  QK_BOOT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    MS_BTN5, MS_BTN1, MS_BTN3, MS_BTN2, MS_BTN4,          MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, MS_BTN1,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, KC_NO,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
),

[_L7] = LAYOUT_split_3x5_3(
    QK_CLEAR_EEPROM, KC_NO, RGB_VAD, RGB_VAI, RGB_TOG, KC_NO, KC_NO,   KC_BRID, KC_BRIU, KC_NO,   KC_NO,
    QK_BOOT,         KC_NO, RGB_HUD, RGB_HUI, KC_NO,          KC_MUTE, KC_VOLD, KC_VOLU, KC_NO,   KC_NO,
    QK_REBOOT, KC_NO,   RGB_SAD, RGB_SAI, KC_NO,           KC_MPLY, KC_MPRV, KC_MNXT, KC_NO,   KC_NO,
    KC_TRNS, LT(_L6, KC_NO), KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
)
};

/**
 * COMBOS
 * Combos allow triggering actions by pressing multiple keys simultaneously.
 * - combo1/2: Trigger Layer 7 (System settings).
 * - combo3: Toggle Layer 3.
 * - combo4/5: Reboot into Bootloader (Flash mode).
 * - combo_caps: Toggle Caps Lock.
 */
const uint16_t PROGMEM combo1[] = { RGUI_T(KC_M), MT(MOD_LGUI, KC_ENT), COMBO_END };
const uint16_t PROGMEM combo2[] = { RGUI_T(KC_V), MT(MOD_LGUI, KC_SPC), COMBO_END };
const uint16_t PROGMEM combo3[] = { LT(_L6, KC_ESC), LT(_L5, KC_BSPC), COMBO_END };
const uint16_t PROGMEM combo4[] = { LT(_L6, KC_NO), LT(_L5, KC_BSPC), COMBO_END };
const uint16_t PROGMEM combo5[] = { KC_Q, KC_W, KC_E, KC_T, COMBO_END };
const uint16_t PROGMEM combo6[] = { KC_Y, KC_I, KC_O, KC_P, COMBO_END };
const uint16_t PROGMEM combo_caps[] = { OSL(_L4), TD(TD_CMENU), COMBO_END };

combo_t key_combos[] = {
    COMBO(combo1, MO(_L7)),
    COMBO(combo2, MO(_L7)),
    COMBO(combo3, TG(_L3)),
    COMBO(combo4, TG(_L3)),
    COMBO(combo5, QK_BOOT),
    COMBO(combo6, QK_BOOT),
    COMBO(combo_caps, KC_CAPS)
};
