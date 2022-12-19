/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
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
 
 /**
  * References:
  * Combining keypresses <https://github.com/qmk/qmk_firmware/issues/6175>
  * Using custom keycodes <https://github.com/bmijanovich/qmk_firmware/blob/ploopy_classic_mac/keyboards/ploopyco/trackball/keymaps/bmijanovich/keymap.c>
  * Tap Dance examples for Ploopy <https://old.reddit.com/r/ploopy/comments/on2unc/tap_dance_examples_for_ploopy/>
  * Another taphold workaround using tap dance <https://blog.slinkyworks.net/running-custom-qmk-on-a-ploopy-mini-trackball/>
  * ploopyco/trackball/readme.md https://github.com/qmk/qmk_firmware/blob/master/keyboards/ploopyco/trackball/readme.md
  **/
 
#include QMK_KEYBOARD_H

enum layer_names {
  _BASE = 0,
  _FN,
};

// Macro Definitions
#define CTLW     LCTL(KC_W)

enum custom_keycodes{
  KC_DRGSCRL = PLOOPY_SAFE_RANGE, // safe range starts at `PLOOPY_SAFE_RANGE` instead.
  KC_DBL_PGUP,
  KC_DBL_PGDN
};

// Track drag scrolling state
static bool drag_scroll_active = false;

// ************************************************ //
// ** Hook functions for sending custom keycodes ** //
// ************************************************ //
/* 
 * QMK functions can't register custom keycodes, but we can setup a keyrecord_t and call process_record_kb() directly.
 * Unknowns:
 *  Do we need to set the column and row for each keycode?
 *  Could reusing the same keyrecord_t struct cause problems with keycodes clobbering each other?
*/
// Dummy keyrecord_t for hooking process_record_kb() with custom keycodes
static keyrecord_t dummy_record = {
    .event = {
        .key = {
            .col = 0,
            .row = 0,
            },
        .pressed = false,
        .time = 0,
    },
    .tap = {0},
};

// Setup dummy_record for process_record_kb()
void setup_dummy_record(uint8_t col, uint8_t row, bool pressed) {
    dummy_record.event.key.col = col;
    dummy_record.event.key.row = row;
    dummy_record.event.pressed = pressed;
    dummy_record.event.time = timer_read();
}

// Register a custom keycode with process_record_kb()
void register_custom_keycode(uint16_t keycode, uint8_t col, uint8_t row) {
    setup_dummy_record(col, row, true);
    process_record_kb(keycode, &dummy_record);
}

// Unregister a custom keycode with process_record_kb()
void unregister_custom_keycode(uint16_t keycode, uint8_t col, uint8_t row) {
    setup_dummy_record(col, row, false);
    process_record_kb(keycode, &dummy_record);
}

// Tap a custom keycode with process_record_kb()
void tap_custom_keycode(uint16_t keycode, uint8_t col, uint8_t row) {
    register_custom_keycode(keycode, col, row);
    wait_ms(10);
    unregister_custom_keycode(keycode, col, row);
}
/* End functions for sending custom keycodes */

// ************************************************ //
// ******** Configuration for Tap Dance *********** //
// ************************************************ //
// Tap Dance keycodes
enum {
    TD_BTN2,
    TD_BTN4,
    TD_BTN5,
};

// Tap Dance actions
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
    TD_SINGLE_HOLD,
} td_action_t;

// Suports single/double/triple taps and single hold. Favors instant hold when interrupted.
td_action_t get_tap_dance_action(qk_tap_dance_state_t *state) {
    if (state->count == 1) return (state->pressed) ? TD_SINGLE_HOLD : TD_SINGLE_TAP;
    //else if (state->count == 2) return TD_DOUBLE_TAP;
    //else if (state->count == 3) return TD_TRIPLE_TAP;
    else return TD_UNKNOWN;
}

// Reset and allow immediate repeat of a Tap Dance
void hard_reset_tap_dance(qk_tap_dance_state_t *state) {
    state->pressed = false;  // reset_tap_dance() will short circuit without this and we need it to complete
    state->finished = true;  // Don't know if this is needed, but it can't hurt
    reset_tap_dance(state);    
}
/* End shared Tap Dance configuration */


/*
Mouse button 5 Tap Dance configuration
  * Single tap: Forward (BTN5)
  * Double tap: 
  * Single hold: Enable trackball scrolling (DRAG_SCROLL)
*/
static td_action_t btn5_td_action = TD_NONE;

void btn5_td_tap(qk_tap_dance_state_t *state, void *user_data) {
    btn5_td_action = get_tap_dance_action(state);
    /*
    if (btn5_td_action == TD_DOUBLE_TAP) {
        tap_code16(KC_LS);
        hard_reset_tap_dance(state);
    }
    */
}

void btn5_td_finished(qk_tap_dance_state_t *state, void *user_data) {
    btn5_td_action = get_tap_dance_action(state);
    switch (btn5_td_action) {
        case TD_SINGLE_TAP:
            tap_code16(KC_BTN5);
            break;
        case TD_SINGLE_HOLD:
            register_custom_keycode(DRAG_SCROLL, 3, 0); // also try 5, 0?
            layer_on(_FN);          // turn on the _FN layer
            drag_scroll_active = true;
            break;
        default:
            break;
    }
}

void btn5_td_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (btn5_td_action == TD_SINGLE_HOLD) {
        layer_off(_FN);           // turn off the _FN layer
        unregister_custom_keycode(DRAG_SCROLL, 3, 0); // try 5, 0? because column, row
        drag_scroll_active = false;
    }
    btn5_td_action = TD_NONE;
}
/* End mouse button 5 Tap Dance configuration */

// Associate tap dance keys with their functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_BTN5] = ACTION_TAP_DANCE_FN_ADVANCED(btn5_td_tap, btn5_td_finished, btn5_td_reset),
};

// ************************************************ //
// ******************** Keymap ******************** //
// ************************************************ //
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT( 
        KC_BTN1, KC_BTN3, KC_BTN4,
          KC_BTN2, TD(TD_BTN5)
    ),
    [_FN] = LAYOUT(
        _______, CTLW, KC_DBL_PGUP,
          KC_DBL_PGDN, _______
    )
};

// ************************************************ //
// ************** CUSTOM KEY HANDLING ************* //
// ************************************************ //
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;
    switch (keycode) {
      case KC_DBL_PGUP:
        if (pressed) {
          tap_code(KC_PGUP);
          register_code(KC_PGUP);
        } else {
          unregister_code(KC_PGUP);
        }
        return false; // Skip all further processing of this key
      case KC_DBL_PGDN:
        if (pressed) {
          tap_code(KC_PGDN);
          register_code(KC_PGDN);
        } else {
          unregister_code(KC_PGDN);
        }
        return false;
      default:
        return true;
    }
} 

// ************************************************ //
// ** Horizontal Scroll while DRAG_SCROLL active ** //
// ************************************************ //
/*
void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v) {
    if (drag_scroll_active) {
        mouse_report->h = -v;
        pointing_device_set_report(*mouse_report);
        pointing_device_send();
    }
    else {
        mouse_report->h = h;
        mouse_report->v = v;
    }
}
*/
