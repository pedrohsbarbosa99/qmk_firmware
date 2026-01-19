#include "keycodes.h"
#include QMK_KEYBOARD_H


#define Q_HM_A LCTL_T(KC_A)
#define Q_HM_S LALT_T(KC_S)
#define Q_HM_D LGUI_T(KC_D)
#define Q_HM_F LSFT_T(KC_F)

#define Q_HM_J RSFT_T(KC_J)
#define Q_HM_L LALT_T(KC_L)
#define Q_HM_SCLN RCTL_T(KC_SCLN)

// Left hand
#define C_HM_A   LCTL_T(KC_A)
#define C_HM_R   LALT_T(KC_R)
#define C_HM_S   LGUI_T(KC_S)
#define C_HM_T   LSFT_T(KC_T)

// Right hand
#define C_HM_N   RSFT_T(KC_N)
#define C_HM_I   RALT_T(KC_I)
#define C_HM_O   RCTL_T(KC_O)



enum  tap_dance_codes {
    TD_SLSH_QST,
    TD_SCLN,
    TD_COMM,
    TD_DOT,
    TD_QUOT,

};


enum layers {
    _QWERTY,
    _COLEMAK_DH,
    _LOWER,
    _RAISE,
    _ADJUST
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        Q_HM_A,  Q_HM_S,  Q_HM_D,  Q_HM_F,  KC_G,          KC_H,    Q_HM_J,  KC_K,    Q_HM_L,  Q_HM_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          LT(_LOWER, KC_TAB), KC_SPC,    KC_ENT,  LT(_RAISE, KC_BSPC)
    ),

    [_COLEMAK_DH] = LAYOUT_split_3x5_2(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,          KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
        C_HM_A,  C_HM_R,  C_HM_S,  C_HM_T,  KC_G,          KC_M,    C_HM_N,  KC_E,    C_HM_I,  C_HM_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,          KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH,
                          LT(_LOWER, KC_TAB), KC_SPC,    KC_ENT,  LT(_RAISE, KC_BSPC)
    ),

    [_LOWER] = LAYOUT_split_3x5_2(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_NO,         KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_DEL,
        KC_NO,   KC_NO,   KC_NO,   KC_HOME, KC_END,        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_ESC,
                          KC_TRNS, KC_SPC,        KC_ENT,  LT(_ADJUST, KC_BSPC)
    ),

    [_RAISE] = LAYOUT_split_3x5_2(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_LPRN, KC_RPRN, TD(TD_QUOT), KC_TILD, S(KC_SCLN),   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCBR, KC_RCBR, KC_NO,   TD(TD_SLSH_QST), KC_CAPS, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                          KC_NO,   KC_SPC,        KC_ENT,  KC_TRNS
    ),

    [_ADJUST] = LAYOUT_split_3x5_2(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   DF(_QWERTY), DF(_COLEMAK_DH),
                                                              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                          KC_NO,   KC_NO,         KC_NO,  KC_TRNS
    ),
};





void slsh_qst_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        tap_code16(S(KC_SLSH));
    } else {
        if (state->count == 1) {
            tap_code(KC_SLSH);
        }
    }
}


void slsh_qst_reset(tap_dance_state_t *state, void *user_data) {}

void quot_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            // hold -> '
            register_code(KC_QUOT);
        } else {
            // tap -> "
            tap_code16(S(KC_QUOT));
        }
    }
}

void quot_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_QUOT);
}



tap_dance_action_t tap_dance_actions[] = {
    [TD_SLSH_QST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slsh_qst_finished, slsh_qst_reset),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),

};

