// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "ttemayo.h" // included for the is<ModPressed> flags
#include "custom_keycode.h"

/* Tap Dance Definitions */
enum custom_tapdance_actions{
  DEL_DELLINE,
  YANK_YANKLINE,
  MINS_EMDASH,
};

#define TD_dd TD(DEL_DELLINE)   // Tap to delete, double tap to delete line
#define TD_yy TD(YANK_YANKLINE) // Tap to yank, double tap to yank line
#define TD_MINS TD(MINS_EMDASH) // Tap to yank, double tap to yank line

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_TRIPLE_TAP
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

/* Single and Double Tap */
td_state_t cur_dance(qk_tap_dance_state_t *state);

void d_finished(qk_tap_dance_state_t *state, void *user_data);
void d_reset(qk_tap_dance_state_t *state, void *user_data); 
void y_finished(qk_tap_dance_state_t *state, void *user_data);
void y_reset(qk_tap_dance_state_t *state, void *user_data);
void dash_finished(qk_tap_dance_state_t *state, void *user_data);
void dash_reset(qk_tap_dance_state_t *state, void *user_data);

td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) return TD_SINGLE_TAP;
  else if (state->count == 2) return TD_DOUBLE_TAP;
  else return TD_UNKNOWN;
}

td_tap_t dashtap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void dash_finished(qk_tap_dance_state_t *state, void *user_data) {
  dashtap_state.state = cur_dance(state);
  switch (dashtap_state.state) {
    case TD_SINGLE_TAP:
      register_code16(KC_MINS);
      break;
    case TD_DOUBLE_TAP:
      sym_emdash();
      break;
    default: break;
  }
}

void dash_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (dashtap_state.state) {
    case TD_SINGLE_TAP:
      unregister_code16(KC_MINS);
      break;
    case TD_DOUBLE_TAP:
      break;
    default: break;
  }
  dashtap_state.state = TD_NONE;
}

td_tap_t dtap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void d_finished(qk_tap_dance_state_t *state, void *user_data) {
  dtap_state.state = cur_dance(state);
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      if (get_mods() & MOD_MASK_CTRL) {
        del_mods(MOD_MASK_CTRL); // currently not working correctly in Tap Dance
        // VIM_SCROLL_HALF_DOWN();
        set_mods(mod_state);
      } else {
        register_code16(CTLX);
      }
      break;
    case TD_DOUBLE_TAP:
      register_custom_keycode(TD_DEL_DELLINE, 12, 5); // Column Row
      break;
    default: break;
  }
}

void d_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      if (!(get_mods() & MOD_MASK_CTRL)) {
        unregister_code16(CTLX); 
      }
      break;
    case TD_DOUBLE_TAP:
      unregister_custom_keycode(TD_DEL_DELLINE, 12, 5);
      break;
    default: break;
  }
  dtap_state.state = TD_NONE;
}

td_tap_t ytap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void y_finished(qk_tap_dance_state_t *state, void *user_data) {
  dtap_state.state = cur_dance(state);
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      if (isShiftPressed) {
          del_mods(MOD_MASK_SHIFT); // currently not working correctly in Tap Dance
          // VIM_YANK_TO_EOL();
          set_mods(mod_state);
      } else {
        register_code16(CTLC);
      }
      break;
    case TD_DOUBLE_TAP:
      register_custom_keycode(TD_YANK_YANKLINE, 12 ,5);
      break;
    default: break;
  }
}

void y_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (dtap_state.state) {
    case TD_SINGLE_TAP:
      unregister_code16(CTLC); 
      break;
    case TD_DOUBLE_TAP: 
      unregister_custom_keycode(TD_YANK_YANKLINE, 12, 5);
      break;
    default: break;
  }
  dtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [DEL_DELLINE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, d_finished, d_reset),
  [YANK_YANKLINE] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, y_finished, y_reset),
  [MINS_EMDASH] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dash_finished, dash_reset),
};
