// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ttemayo.h"

#ifdef LEADER_ENABLE
bool is_leader_active = false;
#endif // LEADER_ENABLE

/* Flags to track modifier key state */
bool is_meh_f17_pressed     = false;
bool is_rhyper_f20_pressed  = false;
bool is_rctrl_f21_pressed   = false;

/* Flags for Custom Media Mod-taps */
bool is_m_prv_pressed = false; // Media Previous Track
bool is_m_nxt_pressed = false; // Media Next Track

/* Flags to determine hold for auto-encase cursor */
#ifdef TTEMAYO_SYM_MACROS_ENABLE
bool is_s_tilde_pressed = false;
bool is_s_lcblk_pressed = false;
bool is_s_astr_pressed  = false;
bool is_s_pct_pressed   = false;
bool is_s_tgrv_pressed  = false;
bool is_s_grv_pressed   = false;
bool is_s_lbrc_pressed  = false;
bool is_s_lcbr_pressed  = false;
bool is_s_lprn_pressed  = false;
bool is_s_labk_pressed  = false;
bool is_s_dpipe_pressed = false;
bool is_s_quot_pressed  = false;
bool is_s_dquo_pressed  = false;
bool is_s_unds_pressed  = false;
#endif // TTEMAYO_SYM_MACROS_ENABLE

// ************************************************ //
// **************** KEY OVERRIDES ***************** //
// ************************************************ //
#ifdef KEY_OVERRIDE_ENABLE
const key_override_t ko_rshift_tab = 
  ko_make_with_layers_negmods_and_options(MOD_BIT(KC_RSFT)                      // Modifier
                                          , KC_TAB                              // Trigger key
                                          , KC_F22                              // Replacement
                                          , (1 << _BASE)                        // Layers
                                          , (uint8_t) ~MOD_BIT(KC_RSFT)         // Negative_mods
                                          , ko_option_activation_trigger_down); // Options

const key_override_t ko_lshift_lead = 
  ko_make_with_layers_negmods_and_options(MOD_BIT(KC_LSFT)
                                          , KC_LEAD
                                          , KC_F23
                                          , (1 << _BASE)
                                          , (uint8_t) ~MOD_BIT(KC_LSFT)
                                          , ko_option_activation_trigger_down);

const key_override_t ko_rshift_f16 = 
  ko_make_with_layers_negmods_and_options(MOD_BIT(KC_RSFT)
                                          , KC_F16
                                          , KC_PGUP
                                          , (1 << _BASE)
                                          , (uint8_t) ~MOD_BIT(KC_RSFT)
                                          , ko_option_activation_trigger_down);

const key_override_t ko_rshift_prtscr = 
  ko_make_with_layers_negmods_and_options(MOD_BIT(KC_RSFT)
                                          , FT_PSCR
                                          , KC_PGDN
                                          , (1 << _BASE)
                                          , (uint8_t) ~MOD_BIT(KC_RSFT)
                                          , ko_option_activation_trigger_down);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&ko_rshift_tab,
  &ko_lshift_lead,
  &ko_rshift_f16,
  &ko_rshift_prtscr,
	NULL // Null terminate the array of overrides!
};
#endif // KEY_OVERRIDE_ENABLE

// ************************************************ //
// ******* CUSTOM KEYCODES/PROCESS_RECORD ********* //
// ************************************************ //
// Overloaded function for individual keymaps if they need something extra/keyboard specific
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

/* Defines actions for my custom keycodes.
 *  Then runs the _keymap's record handler if not processed here,
 *  and use "NEWPLACEHOLDER" for new safe range 
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  bool is_pressed = record->event.pressed;

# ifndef NO_ACTION_ONESHOT 
  // Store the binary representation of active modifiers
  const uint8_t mod_state = get_mods() | get_oneshot_mods() | get_weak_mods(); 
# else
  const uint8_t mod_state = get_mods() | get_weak_mods(); 
# endif // NO_ACTION_ONESHOT

  /* NOTE: If you want the _keymap to run first, uncomment the 
   *  following line and remove call at bottom of this function 
   */
  // if(!process_record_keymap(keycode, record)) return false;

  switch (keycode) {

    /* Custom Mod-tap, Modifier Tracking */
    case MEH_F17:
      if (record->tap.count && is_pressed) {
        return true; // Return true to continue normal key processing
      } else if (is_pressed) {
        is_meh_f17_pressed = true;
      } else {
        is_meh_f17_pressed = false;
      }
      break;
    
    case HYPR_F20:
      if (record->tap.count && is_pressed) {
        return true;
      } else if (is_pressed) {
        is_rhyper_f20_pressed = true;
      } else {
        is_rhyper_f20_pressed = false;
      }
      break;

    /* Modifying hold portion of a Mod Tap */
    case MPRV_RW: // LT(0, KC_MPRV)
      if (record->tap.count && is_pressed) {
        return true;
      } else if (is_pressed) {
        register_code16(KC_MRWD); // Intercept hold function
      } else {
        unregister_code16(KC_MRWD);
      }
      return false;
    
    case MNXT_FF: // LT(0, KC_MNXT)
      if (record->tap.count && is_pressed) {
        return true;
      } else if (is_pressed) {
        register_code16(KC_MFFD);
      } else {
        unregister_code16(KC_MFFD);
      }
      return false;

    case RCST_F18: // LT(_TRNS, F18)
    { // Add RShift and RCtrl modifiers to hold
      static bool trns_layer_hold_registered;
      if (record->tap.count && is_pressed) {
        return true;
      } else if (is_pressed) {
        register_code16(KC_RSFT); 
        register_code16(KC_RCTL);
        trns_layer_hold_registered = true;
      } else if (trns_layer_hold_registered) {
        unregister_code16(KC_RSFT);
        unregister_code16(KC_RCTL);
        trns_layer_hold_registered = false;
      }
      return true;
    }

    /* Tap Dance, VIM Double tap cases */
#   ifdef TAP_DANCE_ENABLE
    case TD_DEL_DELLINE:
      if(is_pressed) {
        tap_code(KC_HOME);
        tap_code(KC_HOME);
        register_code16(KC_LSHIFT);
          tap_code(KC_END);
        unregister_code16(KC_LSHIFT);
        register_code16(KC_LCTRL);
          tap_code(KC_X);
        unregister_code16(KC_LCTRL);
      }
      return false;

    case TD_YANK_YANKLINE:
      if (is_pressed) {
        tap_code(KC_HOME);
        tap_code(KC_HOME);
        register_code16(KC_LSHIFT);
          tap_code(KC_END);
        unregister_code16(KC_LSHIFT);
        register_code16(KC_LCTRL);
          tap_code(KC_C);
        unregister_code16(KC_LCTRL);
        tap_code(KC_RIGHT);
      }
      return false;
#   endif // TAP_DANCE_ENABLE

    /* Modifier-dependant/Conditional Key-override */
    case CO_F16: // KC_F16
      if(is_pressed && (mod_state == MOD_BIT(KC_LALT))) {
        register_code(KC_F4);
        unregister_code(KC_F4); // prevents holding down for multiple Alt+F4 inputs
        return false;
      }
      return true; // Let QMK process the keycode as usual
    
    case CO_GRV:
      if(is_pressed && (mod_state & MOD_MASK_SHIFT)) {
        register_code16(KC_LALT); 
        register_code16(KC_LCTL);
        register_code16(KC_LGUI);
          register_code(KC_GRAVE);
      } else if (!is_pressed) {
          unregister_code(KC_GRAVE);
        unregister_code16(KC_LGUI);
        unregister_code16(KC_LCTL);
        unregister_code16(KC_LALT);
      }
      return false;

    case CO_RCF21: // RCTL_T(KC_F21)
      if (record->tap.count && is_pressed && (mod_state == MOD_BIT(KC_LSFT))) {
        tap_code(KC_END);
        return false;
      } else if (record->tap.count && is_pressed) {
        return true; // Return true to continue normal key processing
      } else if (is_pressed) {
        is_rctrl_f21_pressed = true;
      } else {
        is_rctrl_f21_pressed = false;
      }
      break;
    
    // "Key Overrides" feature not used here because it only handles non-modifiers as the trigger key
    case CO_LCTL: // KC_LCTL
      if (is_pressed && (mod_state == MOD_BIT(KC_RSFT))) {
        tap_code(KC_HOME);
        return false;
      }
      return true;

#   ifdef TTEMAYO_SYM_MACROS_ENABLE
    /* Modifying Tap part of Mod-Tap */
    case HYPR_T(EMDASH):
      if (record->tap.count && is_pressed) {
        sym_emdash();
        return false; // Return false to ignore further processing of key
      }
      break;
    
    /* Tap: Symbol, Hold: Symbol Encase Cursor */ 
    case S_TILDE:
      if (is_pressed) {
          is_s_tilde_pressed = true;
          s_tilde_timer = timer_read();
          tap_code16_nomods(KC_TILDE);
      } else {
        is_s_tilde_pressed = false;
      }
      return false;

    case S_LCBLK:
      if (is_pressed) {
          is_s_lcblk_pressed = true;
          s_lcblk_timer = timer_read();
          send_macro_nomods(&sym_opencommentblock);
      } else {
        is_s_lcblk_pressed = false;
      }
      return false;
    
    case S_ASTR:
      if (is_pressed) {
          is_s_astr_pressed = true;
          s_astr_timer = timer_read();
          tap_code16_nomods(KC_ASTR);
      } else {
        is_s_astr_pressed = false;
      }
      return false;
    
    case S_PCT:
      if (is_pressed) {
          is_s_pct_pressed = true;
          s_pct_timer = timer_read();
          tap_code16_nomods(KC_PERC);
      } else {
        is_s_pct_pressed = false;
      }
      return false;
    
    case S_TGRV:
      if (is_pressed) {
          is_s_tgrv_pressed = true;
          s_tgrv_timer = timer_read();
          send_macro_nomods(&sym_triplegrave);
      } else {
        is_s_tgrv_pressed = false;
      }
      return false;
    
    case S_GRV:
      if (is_pressed) {
          is_s_grv_pressed = true;
          s_grv_timer = timer_read();
          tap_code16_nomods(KC_GRV);
      } else {
        is_s_grv_pressed = false;
      }
      return false;

    case S_LBRC:
      if (is_pressed) {
          is_s_lbrc_pressed = true;
          s_lbrc_timer = timer_read();
          tap_code16_nomods(KC_LBRC);
      } else {
        is_s_lbrc_pressed = false;
      }
      return false;
        
    case S_LCBR:
      if (is_pressed) {
          is_s_lcbr_pressed = true;
          s_lcbr_timer = timer_read();
          tap_code16_nomods(KC_LCBR);
      } else {
        is_s_lcbr_pressed = false;
      } 
      return false;
        
    case S_LPRN:
      if (is_pressed) {
          is_s_lprn_pressed = true;
          s_lprn_timer = timer_read();
          tap_code16_nomods(KC_LPRN);
      } else {
        is_s_lprn_pressed = false;
      } 
      return false;
        
    case S_LABK:
      if (is_pressed) {
          is_s_labk_pressed = true;
          s_labk_timer = timer_read();
          tap_code16_nomods(KC_LABK);
      } else {
        is_s_labk_pressed = false;
      } 
      return false;

    case S_DPIPE:
      if (is_pressed) {
          is_s_dpipe_pressed = true;
          s_dpipe_timer = timer_read();
          send_macro_nomods(&sym_doublepipe);
      } else {
        is_s_dpipe_pressed = false;
      }
      return false;

    case S_QUOT:
      if (is_pressed) {
          is_s_quot_pressed = true;
          s_quot_timer = timer_read();
          tap_code16_nomods(KC_QUOT);
      } else {
        is_s_quot_pressed = false;
      } 
      return false;
    
    case S_DQUO:
      if (is_pressed) {
          is_s_dquo_pressed = true;
          s_dquo_timer = timer_read();
          tap_code16_nomods(KC_DQUO);
      } else {
        is_s_dquo_pressed = false;
      } 
      return false;

    case S_UNDS:
      if (is_pressed) {
          is_s_unds_pressed = true;
          s_unds_timer = timer_read();
          tap_code16_nomods(KC_UNDS);
      } else {
        is_s_unds_pressed = false;
      } 
      return false;
    
    /* Send Symbol */ 
    case S_RCBLK:
      if (is_pressed) {
          send_macro_nomods(&sym_closecommentblock);
      } 
      return false;

    case S_RABK:
      if (is_pressed) {
          tap_code16_nomods(KC_RABK);
      } 
      return false;
        
    case S_RPRN:
      if (is_pressed) {
          tap_code16_nomods(KC_RPRN);
      } 
      return false;
        
    case S_RCBR:
      if (is_pressed) {
          tap_code16_nomods(KC_RCBR);
      } 
      return false;
        
    case S_RBRC:
      if (is_pressed) {
          tap_code16_nomods(KC_RBRC);
      } 
      return false;

    /* Unicode Characters */
    case EMDASH:
      if (is_pressed) {
        send_macro_nomods(&sym_emdash);
      }
      return false;

    /* Biagram/Other Symbols */
    case ARROWOP:
      if (is_pressed) {
        send_macro_nomods(&sym_arrowoperator);
      }
      return false;

    case ARROWFN:
      if (is_pressed) {
        send_macro_nomods(&sym_arrowfunction);
      }
      return false;
    
    case SUBASS:
      if (is_pressed) {
        send_macro_nomods(&sym_subtractassign);
      }
      return false;
    
    case DECROP:
      if (is_pressed) {
        send_macro_nomods(&sym_decrementoperator);
      }
      return false;

    case NOTEQ:
      if (is_pressed) {
        send_macro_nomods(&sym_notequal);
      }
      return false;

    case LESSEQ:
      if (is_pressed) {
        send_macro_nomods(&sym_lessequal);
      }
      return false;

    case GRTREQ:
      if (is_pressed) {
        send_macro_nomods(&sym_greaterequal);
      }
      return false;

    case EQTO:
      if (is_pressed) {
        send_macro_nomods(&sym_equalto);
      }
      return false;
    
    case TILSLSH:
      if (is_pressed) {
        send_macro_nomods(&sym_tildeslash);
      }
      return false;

#   endif // TTEMAYO_SYM_MACROS_ENABLE
  }
  return process_record_keymap(keycode, record);
}

// ************************************************ // 
// *********** KEYBOARD PRE/POST INIT ************* // 
// ************************************************ // 
__attribute__((weak)) void keyboard_pre_init_keymap(void) {}
__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_pre_init_user(void) {
  keyboard_pre_init_keymap();
}

void keyboard_post_init_user(void) {
  numlock_on_init();
# ifdef RGBLIGHT_ENABLE
  rgblight_disable_noeeprom();
# endif // RGBLIGHT_ENABLE

  keyboard_post_init_keymap();
}

// Numlock on boot <https://github.com/qmk/qmk_firmware/issues/10890#issuecomment-927222187>
void numlock_on_init(void) {
  led_t led_state = host_keyboard_led_state();
  bool isNumlock = led_state.num_lock;
  if (!isNumlock) {
    tap_code16(KC_NUM_LOCK);
  }
}

// ************************************************ // 
// ************** LEADER KEY MACROS *************** // 
// ************************************************ // 
#ifdef LEADER_ENABLE
/* Encase Cursor Macros*/
// Block Comment, / * ▌ * / 
void ldr_encase_blkcomment(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "/*  */" 
    SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Asterisk, *▌* 
void ldr_encase_asterisk(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "**" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Percent,  %▌% 
void ldr_encase_pct(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "%%" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Markdown Block Code, ```▌```
void ldr_encase_gravetriple(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "``````" 
    SS_TAP(X_LEFT)SS_TAP(X_LEFT)SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Grave, `▌`
void ldr_encase_grave(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "``" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Square Bracket, [▌]
void ldr_encase_bracket(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "[]" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Curly Brace, {▌}
void ldr_encase_curlybrace(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "{}" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Parenthesis, (▌)
void ldr_encase_paren(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "()" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

// Angle Bracket, <▌>
void ldr_encase_angbracket(void) {
  SEND_STRING (
    SS_LCTL("c") 
    "<>" 
    SS_TAP(X_LEFT)
    SS_LCTL("v")
  );
}

LEADER_EXTERNS(); // Keep this line above matrix_scan_user
#endif // LEADER_ENABLE

// ************************************************ // 
// ***************** MATRIX SCAN ****************** // 
// ************************************************ // 
__attribute__((weak)) void matrix_scan_keymap(void) {}

void matrix_scan_user(void) { 

  /* Tracking Symbol Key Hold w/Timer */
# ifdef TTEMAYO_SYM_MACROS_ENABLE
  if (is_s_tilde_pressed) {
    if (timer_elapsed(s_tilde_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("~" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_lcblk_pressed) {
    if (timer_elapsed(s_lcblk_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR(" */" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT)));
    }
  }

  if (is_s_astr_pressed) {
    if (timer_elapsed(s_astr_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("*" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_pct_pressed) {
    if (timer_elapsed(s_pct_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("%" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_tgrv_pressed) {
    if (timer_elapsed(s_tgrv_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("```" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT)));
    }
  }

  if (is_s_grv_pressed) {
    if (timer_elapsed(s_grv_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("`" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_lbrc_pressed) {
    if (timer_elapsed(s_lbrc_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("]" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_lcbr_pressed) {
    if (timer_elapsed(s_lcbr_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("}" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_lprn_pressed) {
    if (timer_elapsed(s_lprn_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR(")" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_labk_pressed) {
    if (timer_elapsed(s_labk_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR(">" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_dpipe_pressed) {
    if (timer_elapsed(s_dpipe_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("||" SS_TAP(X_LEFT) SS_TAP(X_LEFT)));
    }
  }

  if (is_s_quot_pressed) {
    if (timer_elapsed(s_quot_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("'" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_dquo_pressed) {
    if (timer_elapsed(s_dquo_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("\"" SS_TAP(X_LEFT)));
    }
  }

  if (is_s_unds_pressed) {
    if (timer_elapsed(s_unds_timer) == TAPPING_TERM + 25) {
      send_string_nomods(PSTR("_" SS_TAP(X_LEFT)));
    }
  }
# endif // TTEMAYO_SYM_MACROS_ENABLE

# ifdef LEADER_ENABLE
  LEADER_DICTIONARY() {
    leading = false; // do not remove

    // ***** Caps Lock Sequence***** //
    SEQ_ONE_KEY(KC_LEAD) { // Double tap LDR for CAPSLOCK
      tap_code(KC_CAPS);
#     ifdef RGBLIGHT_ENABLE
      if(IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) { // Prevent CAPSLOCK LED desync
        rgblight_enable_noeeprom();
      } else {
        rgblight_disable_noeeprom();
      }
#     endif // RGBLIGHT_ENABLE
    }
    
    /*  Leader Key Encase Selection Reference:
    * ,-----------------------------------------------------------. 
    * | VIM_ESC |         |         |         |         |         |---------. 
    * |---------+---------+---------+---------+---------+---------|         | 
    * |         |         | / *     | *       |         | %       |---------| 
    * |---------+---------+---------+---------+---------+---------|         | 
    * | ```     | `       | [       | {       | (       | <       |---------| 
    * |---------+---------+---------+---------+---------+---------|         | 
    * |         |         |         |         |         |         |---------' 
    * |---------+---------+---------+-----------------------------'
    * |         |         |         |  |         | 
    * `-----------------------------'  `---------'  */
    
    /** R3; TOP ROW QWERTY **/
    SEQ_ONE_KEY(KC_W)   { ldr_encase_blkcomment(); }
    SEQ_ONE_KEY(KC_E)   { ldr_encase_asterisk(); }
    SEQ_ONE_KEY(KC_T)   { ldr_encase_pct(); }
    
    /** R2; HOME ROW QWERTY **/
    SEQ_ONE_KEY(KC_GRV) { ldr_encase_gravetriple(); }
    SEQ_ONE_KEY(KC_A)   { ldr_encase_grave(); }
    SEQ_ONE_KEY(KC_S)   { ldr_encase_bracket(); }
    SEQ_ONE_KEY(KC_D)   { ldr_encase_curlybrace(); }
    SEQ_ONE_KEY(KC_F)   { ldr_encase_paren(); }
    SEQ_ONE_KEY(KC_G)   { ldr_encase_angbracket(); }
  }
# endif // LEADER_ENABLE
  matrix_scan_keymap(); 
}

#ifdef LEADER_ENABLE
void leader_start(void) {
  // Sequence started
  is_leader_active = true;
}

void leader_end(void) {
  // Sequence ended (no success/failure detection)
  is_leader_active = false;
}
# endif // LEADER_ENABLE

// ************************************************ //
// ****** BIAGRAM and UNICODE SYMBOL MACROS ******* //
// ************************************************ // 
#ifdef TTEMAYO_SYM_MACROS_ENABLE
void sym_emdash(void) {
  register_code16(KC_RALT);
    tap_code(KC_KP_0);
    tap_code(KC_KP_1);
    tap_code(KC_KP_5);
    tap_code(KC_KP_1);
  unregister_code16(KC_RALT);
}
void sym_subtractassign(void)     { SEND_STRING("-="); }
void sym_decrementoperator(void)  { SEND_STRING("--"); }
void sym_arrowoperator(void)      { SEND_STRING("->"); }
void sym_arrowfunction(void)      { SEND_STRING("=>"); }
void sym_notequal(void)           { SEND_STRING("!="); }
void sym_lessequal(void)          { SEND_STRING("<="); }
void sym_greaterequal(void)       { SEND_STRING(">="); }
void sym_equalto(void)            { SEND_STRING("=="); }
void sym_opencommentblock(void)   { SEND_STRING("/* "); }
void sym_closecommentblock(void)  { SEND_STRING(" */"); }
void sym_triplegrave(void)        { SEND_STRING("```"); }
void sym_doublepipe(void)         { SEND_STRING("||"); }
void sym_tildeslash(void)         { SEND_STRING("~/."); }
#endif // TTEMAYO_SYM_MACROS_ENABLE

// ************************************************ // 
// ************* LAYER RGB INDICATORS ************* // 
// ************************************************ // 
#ifdef RGB_MATRIX_ENABLE
  /* Leader Key per-key LED  */
  // void rgb_matrix_indicators_user(void) { 
  //     if (is_leader_active) {
  //         rgb_matrix_set_color_hsv(14, 999, 999, 999, 1); // CONFIG
  //         rgb_matrix_set_color_hsv(30, 999, 999, 999, 1); // CONFIG
  //     } else {
  //         rgb_matrix_set_color_hsv(14, 999, 999, 999, led_dim_ratio); // CONFIG
  //     }  
  // }
#endif // RGB_MATRIX_ENABLE

#ifdef RGBLIGHT_ENABLE
  /* WIP Code for layer state LED underglow */
  // layer_state_t layer_state_set_user(layer_state_t state) {
  //     switch (get_highest_layer(state)) {
  //     case _BASE:
  //         rgblight_sethsv_noeeprom(HSV_GOLD);
  //         break;
  //     case _ADJUST:
  //         rgblight_sethsv_noeeprom(HSV_RED);
  //         break;
  //     default: //  for any other layers, or the default layer
  //         rgblight_sethsv_noeeprom(HSV_OFF);
  //         break;
  //     }
  //   return state;
  // }
#endif // RGBLIGHT_ENABLE

// ************************************************ // 
// ********** "WORD BREAKING" CAPS WORD  ********** // 
// ************************************************ // 
bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue Caps Word, with shift applied.
    case KC_A ... KC_Z:
    case KC_MINS:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
      return true;

    // Keycodes that continue Caps Word, without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
    case KC_LEAD: // Add Leader key exception
    case KC_LSFT:
    case KC_RSFT: 
    case LT_VIM: // ergodash/rev1/ttemayo specific
      return true;

    default:
      return false;  // Deactivate Caps Word
  }
}

/* Helper functions to invoke Right Hyper */
void register_rhyper (void) { 
  register_code (KC_RSFT);
  register_code (KC_RCTL);
  register_code (KC_RALT);
  register_code (KC_RGUI);
}

void unregister_rhyper (void) { 
  unregister_code (KC_RSFT);
  unregister_code (KC_RCTL);
  unregister_code (KC_RALT);
  unregister_code (KC_RGUI);
}

/**
 * @brief Tap keycode, with no mods
 *
 * @param kc keycode to use
 */
void tap_code16_nomods(uint16_t kc) {
  uint8_t temp_mod = get_mods();
  clear_mods();
  #ifndef NO_ACTION_ONESHOT
  clear_oneshot_mods();
  #endif  // NO_ACTION_ONESHOT
  tap_code16(kc);
  set_mods(temp_mod);
}

/**
 * @brief Call macro function, with no mods
 *
 * @param func void macro function() to call 
 */
void send_macro_nomods(void (*func)(void)) {
  uint8_t temp_mod = get_mods();
  clear_mods();
  #ifndef NO_ACTION_ONESHOT
  clear_oneshot_mods();
  #endif  // NO_ACTION_ONESHOT
  (*func)();
  set_mods(temp_mod);
}

/**
 * @brief Call send_string_P function, with no mods
 *
 * @param string string to pass to send_string_P()
 */
void send_string_nomods(const char *string) {
  uint8_t temp_mod = get_mods();
  clear_mods();
  #ifndef NO_ACTION_ONESHOT
  clear_oneshot_mods();
  #endif  // NO_ACTION_ONESHOT
  // send_string_P(PSTR(string)); // Gives "error: invalid initializer"
  send_string_P(string);
  set_mods(temp_mod);
}

/**
 * @brief Performs exact match for modifier values
 *
 * @param value the modifer variable (get_mods/get_oneshot_mods/get_weak_mods)
 * @param mask the modifier mask to check for
 * @return true Has the exact modifiers specifed
 * @return false Does not have the exact modifiers specified
 */
bool hasAllBitsInMask(uint8_t value, uint8_t mask) {
  value &= 0xF;
  mask &= 0xF;

  return (value & mask) == mask;
}
