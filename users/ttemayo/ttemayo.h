// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#ifdef VIMDOWS_ENABLE
# include "vimdows.h" // SAFE_RANGE visibility
#endif // VIMDOWS_ENABLE

bool on_mac; // Future feature flag to toggle for Mac functionality
bool is_leader_active; // Future feature flag to update LEDs or Display
bool is_scroll_locked;

/* Flags to track modifier key state */
extern bool is_meh_f17_pressed;
extern bool is_rhyper_f20_pressed;
extern bool is_rctrl_f21_pressed;

/* Track key states for tap/hold media keys */
bool is_m_prv_pressed;
bool is_m_nxt_pressed;

#ifdef TTEMAYO_SYM_MACROS_ENABLE
/* Timers to evaluate hold for symbol encasing cursor */
uint16_t s_tilde_timer;
uint16_t s_lcblk_timer;
uint16_t s_astr_timer;
uint16_t s_pct_timer;
uint16_t s_tgrv_timer;
uint16_t s_grv_timer;
uint16_t s_lbrc_timer;
uint16_t s_lcbr_timer;
uint16_t s_lprn_timer;
uint16_t s_labk_timer;
uint16_t s_dpipe_timer;
uint16_t s_quot_timer;
uint16_t s_dquo_timer;
uint16_t s_unds_timer;

/* Track key states for symbol encasing cursor */
bool is_s_tilde_pressed;
bool is_s_lcblk_pressed;
bool is_s_astr_pressed;
bool is_s_pct_pressed;
bool is_s_tgrv_pressed;
bool is_s_grv_pressed;
bool is_s_lbrc_pressed;
bool is_s_lcbr_pressed;
bool is_s_lprn_pressed;
bool is_s_labk_pressed;
bool is_s_dpipe_pressed;
bool is_s_quot_pressed;
bool is_s_dquo_pressed;
bool is_s_unds_pressed;
#endif // TTEMAYO_SYM_MACROS_ENABLE

enum userspace_layer_names {
  _BASE = 0,  // = 0; QWERTY
  _TRNS,      // = 1; Transparent Layer for tri-state layer shenanigans
  _FN,        // = 2; F-keys
  _NUM,       // = 3; Numpad
  _MOUSE,     // = 4; Mouse Keys
  _VIMTOGGLE, // = 5; Move to VIM layer, access to to Insert-mode keys
  _VIM,       // = 6; Momentary VIM layer and Media keys
  _SYM,       // = 7; Symbols
};

enum userspace_custom_keycodes {
# ifdef VIMDOWS_ENABLE
  PLACEHOLDER = VIM_SAFE_RANGE,
# else
  PLACEHOLDER = SAFE_RANGE,
# endif // VIMDOWS_ENABLE
  S_TILDE,  // Tap ~    Hold to encase cursor ~
  S_LCBLK,  // Tap /*   Hold to encase cursor */
  S_ASTR,   // Tap *    Hold to encase cursor *
  S_PCT,    // Tap %    Hold to encase cursor %
  S_TGRV,   // Tap ```  Hold to encase cursor ```
  S_GRV,    // Tap `    Hold to encase cursor `
  S_DPIPE,  // Tap ||   Hold to encase cursor ||
  S_LBRC,   // Tap [    Hold to encase cursor ]
  S_LCBR,   // Tap {    Hold to encase cursor }
  S_LPRN,   // Tap (    Hold to encase cursor )
  S_LABK,   // Tap <    Hold to encase cursor >
  S_QUOT,   // Tap '    Hold to encase cursor '
  S_DQUO,   // Tap "    Hold to encase cursor "
  S_UNDS,   // Tap _    Hold to encase cursor _
  S_RCBLK,  // */
  S_RABK,   // >
  S_RPRN,   // )
  S_RCBR,   // }
  S_RBRC,   // ]
  EMDASH,   // —
  ARROWOP,  // ->
  ARROWFN,  // =>
  SUBASS,   // -=
  DECROP,   // --
  NOTEQ,    // !=
  LESSEQ,   // <=
  GRTREQ,   // >=
  EQTO,     // ==
  TILSLSH,  // ~/.
  /* Conditional Key Override */
  CO_GRV,   // " for HYPER(`)
  NEW_SAFE_RANGE,
};

#ifdef TAP_DANCE_ENABLE
enum userspace_tapdance_index {
  TD_PLACEHOLDER = NEW_SAFE_RANGE,
  TD_YANK_YANKLINE,
  TD_DEL_DELLINE,
  TD_MINS_EMDASH,
  TD_SAFE_RANGE,
};
#endif // TAP_DANCE_ENABLE

// ************************************************ //
// *************** Keycode Aliases *************** //
// ************************************************ // 
/* Custom Mod-Tap Keys */
#define RCA_T(kc)   MT(MOD_RCTL | MOD_RALT, kc) // Right Control + Alt
#define RHYPR_T(kc) MT(MOD_RCTL | MOD_RSFT | MOD_RALT | MOD_RGUI, kc) // Right Mod-tap Hyper
#define RHYPR(kc)   (QK_RCTL | QK_RSFT | QK_RALT | QK_RGUI | (kc))
#define KC_RHYPR    HYPR(KC_NO) // Dedicated keycode version of Right Hyper

/* HOLD: Momentary Layer, TAP: a Keycode */
#define FT_PSCR   LT(_FN,KC_PSCR) // HOLD: Function Layer Toggle, TAP: Print Screen
#define FT_BSLS   LT(_FN,KC_BSLS) // HOLD: Function Layer Toggle, TAP: Backslash 

/* Mod Tap */
#define MEH_F17   MEH_T(KC_F17)   // HOLD: Left Control, Shift and Alt,        TAP: F17
#define LCS_F18   C_S_T(KC_F18)   // HOLD: Left Control & Shift,               TAP: F18
#define RALT_F19  RALT_T(KC_F19)  // HOLD: Right Alt,                          TAP: F19
#define RCA_BRK   RCA_T(KC_BRK)   // HOLD: Right Control, Alt,                 TAP: Pause/Break
#define HYPR_F20  RHYPR_T(KC_F20) // HOLD: Right Control, Shift, Alt, and GUI, TAP: F20
#define RCTL_F21  RCTL_T(KC_F21)  // HOLD: Right Control,                      TAP: F21

/* Mod Tap w/HOLD portion modified */
#define MPRV_RW   LT(0, KC_MPRV)  // HOLD: Rewind,                             TAP: Media Previous Track
#define MNXT_FF   LT(0, KC_MNXT)  // HOLD: Fastforward,                        TAP: Media Next Track
#define RCST_F18  LT(1, KC_F18)   // HOLD: RCtl, RShift & TRNS Layer Toggle,   TAP: F18

/* Mod Tap w/TAP portion modified */
#define ALL_EMD   HYPR_T(EMDASH)  // HOLD: Left Control, Shift, Alt, and GUI, TAP: Em-Dash

/* Modifier/Conditional Key Override */
#define CO_F16    KC_F16    // F16 when un-modified, other depending on modifier state
#define CO_RCF21  RCTL_F21  // HOLD: Right Control, TAP: F21, SHIFT TAP: END
#define CO_LCTL   KC_LCTL   // HOLD: LCTL, TAP: LCTL, SHIFT TAP: HOME 

#define CTLC  LCTL(KC_C)  // LCtrl + C
#define CTLX  LCTL(KC_X)  // LCtrl + X
#define CTLF  LCTL(KC_F)  // LCtrl + F

#define S_HOME  S(KC_HOME)
#define S_END   S(KC_END)

void numlock_on_init(void); // Function for turning ON numlock at keyboard init

#ifdef LEADER_ENABLE
void leader_start(void); // Automatically called Leader Key functions when sequence is started
void leader_end(void);   //  or ended.
/* Selection Encasing Macros */
void ldr_encase_pct(void);
void ldr_encase_blkcomment(void);
void ldr_encase_asterisk(void);
void ldr_encase_grave(void);
void ldr_encase_bracket(void);
void ldr_encase_curlybrace(void);
void ldr_encase_paren(void);
void ldr_encase_angbracket(void);
void ldr_encase_gravetriple(void);
#endif // LEADER_ENABLE

/* Symbol Macros */
#ifdef TTEMAYO_SYM_MACROS_ENABLE
void sym_emdash(void);            // — (ALT 250)
void sym_arrowoperator(void);     // ->
void sym_arrowfunction(void);     // =>
void sym_subtractassign(void);    // -=
void sym_decrementoperator(void); // --
void sym_notequal(void);          // !=
void sym_lessequal(void);         // <=
void sym_greaterequal(void);      // >=
void sym_equalto(void);           // ==
void sym_opencommentblock(void);  // /*
void sym_closecommentblock(void); // */
void sym_triplegrave(void);       // ```
void sym_doublepipe(void);        // ||
void sym_tildeslash(void);        // ~/.
#endif // TTEMAYO_SYM_MACROS_ENABLE

void register_rhyper (void);
void unregister_rhyper (void);
void tap_code16_nomods(uint16_t kc);
void send_macro_nomods(void (*func)(void));
void send_string_nomods(const char *string);
bool hasAllBitsInMask(uint8_t value, uint8_t mask);
