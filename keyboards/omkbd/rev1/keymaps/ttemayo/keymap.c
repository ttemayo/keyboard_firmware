// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "ttemayo.h"
#include "vimdows.h"
#include "custom_keycode.h"
#ifdef TAP_DANCE_ENABLE
#  include "tapdance.h"
#endif // TAP_DANCE_ENABLE

// Filler key due to replacing 1U's with 2U's
#define ___X___ KC_NO 

static uint16_t previous_layer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: BASE layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------. 
   * | VIM_ESC | !1      | @2      | #3      | $4      | %5      |---------.          ,---------| ^6      | &7      | *8      | (9      | )0      | _-      | 
   * |---------+---------+---------+---------+---------+---------| {[      |          | }]      |---------+---------+---------+---------+---------+---------| 
   * | Tab     | Q       | W       | E       | R       | T       |---------|          |---------| Y       | U       | I       | O       | P       | LEADER  | 
   * |---------+---------+---------+---------+---------+---------| F4/16   |          | +=      |---------+---------+---------+---------+---------+---------| 
   * | ~`      | A       | S       | D       | F       | G       |---------|          |---------| H       | J       | K       | L       | :;      | "'      | 
   * |---------+---------+---------+---------+---------+---------| FT(PSCR)|          | FT(|\)  |---------+---------+---------+---------+---------|---------| 
   * | LShift  | Z       | X       | C       | V       | B       |---------'          `---------| N       | M       | <,      | >.      | ?/      | RShift  | 
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------| 
   * | LCtrl   |LMeh(F17)| LGUI    |  | LAlt    |      ,-------------------.          ,-------------------.      |RAlt(F19)|  |RCA(PBrk)|RHyp(F20)|RCtl(F21)| 
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------' 
   *                                                   | Del     |RCST(F18)|          |LT/TO_VIM| Enter   |
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | Space   |         |         |          |         |         | BckSpc  |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_BASE] = LAYOUT_4key_2u_inner (
      VIM_ESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_LBRC,             KC_RBRC,  KC_6,     KC_7,     KC_8,      KC_9,    KC_0,     KC_MINS, 
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     CO_F16,              KC_EQL,   KC_Y,     KC_U,     KC_I,      KC_O,    KC_P,     KC_LEAD, 
      KC_GRV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     FT_PSCR,             FT_BSLS,  KC_H,     KC_J,     KC_K,      KC_L,    KC_SCLN,  KC_QUOT,
      KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     ___X___,             ___X___,  KC_N,     KC_M,     KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT, 
      KC_LCTL,  MEH_F17,  KC_LGUI,  KC_LALT,  KC_SPC,   KC_DEL,   RCST_F18,            LT_VIM,   KC_ENT,   KC_BSPC,  RALT_F19,  RCA_BRK, HYPR_F20, CO_RCF21
      ),
  
  /* Keymap 1: TRANSPARENT (Placeholder) layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------.          ,---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | TRNS    |---------+---------+---------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | TRNS    |---------+---------+---------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          | |\      |---------+---------+---------+---------+---------|---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------'          `---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TRNS    |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    | TRNS    |          | TRNS    | TRNS    |        
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_TRNS] = LAYOUT_4key_2u_inner (
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,             KC_BSLS,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  ___X___,             ___X___,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______
      ),

  /* Keymap 2: FUNCTION layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | TRNS    | F1      | F2      | F3      | F4      | F5      |---------.          ,---------| F6      | F7      | F8      | F9      | F10     | TRNS    |
   * |---------+---------+---------+---------+---------+---------| F11     |          | F12     |---------+---------+---------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | TRNS    |---------+---------+---------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------|          |---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          | |\      |---------+---------+---------+---------+---------|---------|
   * | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |---------'          `---------| TRNS    | TRNS    | TRNS    | TRNS    | TRNS    | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TRNS    |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    | TRNS    |          | TRNS    | TRNS    |        
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_FN] = LAYOUT_4key_2u_inner (
      _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,              KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,             KC_BSLS,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  ___X___,             ___X___,  _______,  _______,  _______,  _______,  _______,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             _______,  _______,  _______,  _______,  _______,  _______,  _______
      ),

  /* Keymap 3: NUMPAD Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | VIM_ESC |  !      |  @      |  #      |  $      |  %      |---------.          ,---------|  ^      |  &      |  *      |  /      |  -      | _-      |
   * |---------+---------+---------+---------+---------+---------| {[      |          | }]      |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         |         |         |         |         |---------|          |---------|  +      |  7      |  8      |  9      |  +      |         |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | +=      |---------+---------+---------+---------+---------+---------|
   * |         |         |         |         |         |         |---------|          |---------|  =      |  4      |  5      |  6      | .       | "'      |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          | |\      |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         |         |         |         |         |---------'          `---------|  0      |  1      |  2      |  3      | Calc    | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TRNS    |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    | CS(F18) |          | MO(_VIM)| TRNS    |
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_NUM] = LAYOUT_4key_2u_inner (
      VIM_ESC,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_LBRC,             KC_RBRC,  KC_CIRC,  KC_AMPR,  KC_PAST,  KC_PSLS,  KC_PMNS,  KC_MINS, 
      _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,             KC_EQL,   KC_PPLS,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  XXXXXXX, 
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PSCR,             KC_BSLS,  KC_PEQL,  KC_P4,    KC_P5,    KC_P6,    KC_PDOT,  KC_QUOT,
      _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  ___X___,             ___X___,  KC_P0,    KC_P1,    KC_P2,    KC_P3,    KC_CALC,  _______, 
      _______,  _______,  _______,  _______,  _______,  _______,  LCS_F18,             MO(_VIM), _______,  _______,  _______,  _______,  _______,  _______
      ),
  #ifdef MOUSEKEY_ENABLE 
  /* Keymap 4: Mouse Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | VIM_ESC |         |         |         |         |         |---------.          ,---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         |Mouse 1  |Mouse Up |Mouse 2  |Wheel Up |---------|          |---------|Wheel Up |Mouse 1  |Mouse Up |Mouse 2  |         |         |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          |         |---------+---------+---------+---------+---------+---------|
   * |         |         |Mouse L  |Mouse Dn |Mouse R  |Wheel Dn |---------|          |---------|Wheel Dn |Mouse L  |Mouse Dn |Mouse R  |         |         |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          |         |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         |Mouse 4  |Mouse 3  |Mouse 5  |         |---------'          `---------|         |Mouse 4  |Mouse 3  |Mouse 5  |         | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TRNS    |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   |Mouse Acc| CS(F18) |          | MO(_VIM)|Mouse Acc|
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_MOUSE] = LAYOUT_4key_2u_inner (
      VIM_ESC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
      _______,  XXXXXXX,  KC_BTN1,  KC_MS_U,  KC_BTN2,  KC_WH_U,  _______,             XXXXXXX,  KC_WH_U,  KC_BTN1,  KC_MS_U,  KC_BTN2,  XXXXXXX,  XXXXXXX, 
      XXXXXXX,  XXXXXXX,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,  KC_PSCR,             XXXXXXX,  KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  XXXXXXX,  XXXXXXX, 
      _______,  XXXXXXX,  KC_BTN4,  KC_BTN3,  KC_BTN5,  XXXXXXX,  ___X___,             ___X___,  XXXXXXX,  KC_BTN4,  KC_BTN3,  KC_BTN5,  XXXXXXX,  _______, 
      _______,  _______,  _______,  _______,  _______,  KC_ACL2,  LCS_F18,             MO(_VIM), KC_ACL2,  _______,  _______,  _______,  _______,  _______
      ),
  #endif // MOUSEKEY_ENABLE 
  /* Keymap 5: VIM (Toggle) Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | VIM_ESC |         |         |         | VIM 4   |         |---------.          ,---------| VIM 6   |         |         |         | VIM 0   |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         | VIM W   | VIM E   | VIM R   |         |---------|          |---------|         | VIM U   | VIM I   | VIM O   | VIM P   |         |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          |         |---------+---------+---------+---------+---------+---------|
   * | CO_GRV  | VIM A   | VIM S   | VIM D   | VIM F   | VIM G   |---------|          |---------| VIM H   | VIM J   | VIM K   | VIM L   | MO(NUM) |         |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          |         |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         | VIM X   | VIM C   | VIM V   | VIM B   |---------'          `---------|         |         |         |         | Ctrl+F  | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TRNS    |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | TRNS    | TRNS    |          | MO(_VIM)| TRNS    |
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_VIMTOGGLE] = LAYOUT_4key_2u_inner (
      VIM_ESC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  VIM_4,    XXXXXXX,  XXXXXXX,             XXXXXXX,  VIM_6,    XXXXXXX,  XXXXXXX,  XXXXXXX,  VIM_0,    XXXXXXX, 
      _______,  XXXXXXX,  VIM_W,    VIM_E,    VIM_R,    XXXXXXX,  _______,             XXXXXXX,  VIM_Y,    VIM_U,    VIM_I,    VIM_O,    VIM_P,    XXXXXXX, 
      CO_GRV,   VIM_A,    VIM_S,    VIM_D,    VIM_F,    VIM_G,    KC_PSCR,             XXXXXXX,  VIM_H,    VIM_J,    VIM_K,    VIM_L,    XXXXXXX,  XXXXXXX,
      _______,  XXXXXXX,  VIM_X,    VIM_C,    VIM_V,    VIM_B,    ___X___,             ___X___,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  CTLF,     _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,             MO(_VIM), _______,  _______,  _______,  _______,  _______,  _______
      ),
     
  /* Keymap 6: VIM/Media (Momentary) layer 
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | VIM_ESC |         |         |         | VIM 4   |         |---------.          ,---------| VIM 6   |         |         |         | VIM 0   |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * | TRNS    |         | VIM W   | VIM E   | VIM R   |         |---------|          |---------| VIM Y   | VIM U   | VIM I   |         | VIM P   |         |
   * |---------+---------+---------+---------+---------+---------| TRNS    |          | Mute    |---------+---------+---------+---------+---------+---------|
   * | CO_GRV  |         |         | VIM D   | VIM F   | VIM G   |---------|          |---------| VIM H   | VIM J   | VIM K   | VIM L   |         |         |
   * |---------+---------+---------+---------+---------+---------| PrtScr  |          | Play    |---------+---------+---------+---------+---------|---------|
   * | TRNS    |         | VIM X   |         | VIM V   | VIM B   |---------'          `---------|Prev/Rwd | Vol -   | Vol +   |Next/Fwd | Ctrl+F  | TRNS    |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * | TRNS    | TRNS    | TRNS    |  | TRNS    |      ,-------------------.          ,-------------------.      | TRNS    |  | TRNS    | TRNS    | TRNS    |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   | Del     | TRNS    |          | TRNS    | Enter   |        
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         | TRNS    |         |         |          |         |         | TRNS    |
   *                                         `-----------------------------'          `-----------------------------'                                      */
	[_VIM] = LAYOUT_4key_2u_inner (
      VIM_ESC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  VIM_4,    XXXXXXX,  XXXXXXX,             XXXXXXX,  VIM_6,    XXXXXXX,  XXXXXXX,  XXXXXXX,  VIM_0,    XXXXXXX, 
      _______,  XXXXXXX,  VIM_W,    VIM_E,    VIM_R,    XXXXXXX,  _______,             KC_MUTE,  VIM_Y,    VIM_U,    VIM_I,    XXXXXXX,  VIM_P,    XXXXXXX, 
      CO_GRV,   XXXXXXX,  XXXXXXX,  VIM_D,    VIM_F,    VIM_G,    KC_PSCR,             KC_MPLY,  VIM_H,    VIM_J,    VIM_K,    VIM_L,    XXXXXXX,  XXXXXXX, 
      _______,  XXXXXXX,  VIM_X,    XXXXXXX,  VIM_V,    VIM_B,    ___X___,             ___X___,  MPRV_RW,  KC_VOLD,  KC_VOLU,  MNXT_FF,  CTLF,     _______, 
      _______,  _______,  _______,  _______,  _______,  KC_DEL,  _______,/*<Keep TRNS>*/_______, KC_ENT,   _______,  _______,  _______,  _______,  _______
      ),

  /* Keymap 7: SYMBOL Layer
   * ,-----------------------------------------------------------.                              ,-----------------------------------------------------------.
   * | VIM_ESC |         |         |         |         |         |---------.          ,---------|         |         |         |         |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * |         |         | ```     | / *     | *       | %       |---------|          |---------|         | —       | * /     | "       |         |         |
   * |---------+---------+---------+---------+---------+---------|         |          |         |---------+---------+---------+---------+---------+---------|
   * | Home    | `       | [       | {       | (       | <       |---------|          |---------| >       | )       | }       | ]       | '       | End     |
   * |---------+---------+---------+---------+---------+---------|         |          | ||      |---------+---------+---------+---------+---------|---------|
   * | S(Home) | ~       | >=      | <=      | !=      | ==      |---------'          `---------| --      | ->      | =>      | -=      | _       | S(End)  |
   * |---------+---------+---------+-----------------------------'                              `-----------------------------+---------+---------+---------|
   * |         |         |         |  |         |      ,-------------------.          ,-------------------.      |         |  |         |         |         |
   * `-----------------------------'  `---------'      |         |         |          |         |         |      `---------'  `-----------------------------'
   *                                                   |         |         |          |         |         |
   *                                         ,---------|         |         |          |         |         +---------.
   *                                         |         |         |         |          |         |         |         |
   *                                         `-----------------------------'          `-----------------------------'                                      */
  [_SYM] = LAYOUT_4key_2u_inner (
      VIM_ESC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, 
      XXXXXXX,  XXXXXXX,  S_TGRV,   S_LCBLK,  S_ASTR,   S_PCT,    XXXXXXX,             XXXXXXX,  XXXXXXX,  EMDASH,   S_RCBLK,  S_DQUO,   XXXXXXX,  XXXXXXX, 
      S_HOME,   S_GRV,    S_LBRC,   S_LCBR,   S_LPRN,   S_LABK,   XXXXXXX,             S_DPIPE,  S_RABK,   S_RPRN,   S_RCBR,   S_RBRC,   S_QUOT,   S_END, 
      KC_HOME,  S_TILDE,  GRTREQ,   LESSEQ,   NOTEQ,    EQTO,     ___X___,             ___X___,  DECROP,   ARROWOP,  ARROWFN,  SUBASS,   S_UNDS,   KC_END, 
      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
      )
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

  bool is_pressed = record->event.pressed;

# ifndef NO_ACTION_ONESHOT 
  // Store the binary representation of active modifiers
  const uint8_t mod_state = get_mods() | get_oneshot_mods() | get_weak_mods(); 
# else
  const uint8_t mod_state = get_mods() | get_weak_mods(); 
# endif // NO_ACTION_ONESHOT

  switch (keycode) { 

    /* Layer Toggle Chords */
#   ifdef MOUSEKEY_ENABLE 
    case KC_DEL:
      if (is_pressed && is_meh_f17_pressed && layer_state_is(_BASE)) {
        layer_move(_MOUSE);
        return false;
      }
      return true;
#   endif // MOUSEKEY_ENABLE 

    case KC_ENTER:
      if (is_pressed && is_rhyper_f20_pressed && layer_state_is(_BASE)) {
        layer_move(_NUM);
        return false;
      }
      return true;

    /* Keymap-specific, Vim-related Custom Keycodes */
    case VIM_ESC: 
    {
      static bool vim_esckey_registered; // Track Esc key status to release on else clause
      if (is_pressed && (get_mods() == MOD_BIT(KC_RSFT))) {
#       ifdef TTEMAYO_SYM_MACROS_ENABLE
        del_mods(MOD_BIT(KC_RSFT));
        sym_emdash();
        set_mods(mod_state);
#       endif // TTEMAYO_SYM_MACROS_ENABLE
      } else if (is_pressed) {
        switch(VIM_QUEUE) {
          case VIM_R: VIM_LEFT(); break;
          default: 
            PRESS(KC_ESC);
            vim_esckey_registered = true;
#           ifdef CAPS_WORD_ENABLE
            caps_word_off();
#           endif // CAPS_WORD_ENABLE
            layer_move(_BASE);
            if(IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
              TAP(KC_CAPS); // Turn off Capslock, if on
            }
            VIM_LEADER(KC_NO); // Clear the VIM Leader queue
          break;
        }
      } else { // Do something when key released; Typically unregister keycode
        if (vim_esckey_registered) {
          RELEASE(KC_ESC);
          vim_esckey_registered = false;
        }
      }
      return false; // Skip all further processing of this key
    }

    case LTTO_VIM:                                  
      if(is_pressed) {
        ltto_vim_timer = timer_read();
        layer_on(_VIM); // Needs transparent layer to see keypress release()?
      } else {
        layer_off(_VIM);
        VIM_LEADER(KC_NO);
        if (is_rctrl_f21_pressed 
          && (timer_elapsed(ltto_vim_timer) < TAPPING_TERM + 50) 
          && layer_state_is(_BASE)) {  
          layer_move(_VIMTOGGLE); // same as TO(_VIMTOGGLE)
        }
      }
      return true; 

    // ************************************************ //
    // ******** vimdows.h KEYCODE Implementation ****** //
    // ************************************************ //
    case VIM_0:
      if (is_pressed) {
        VIM_BEGINNING_OF_LINE();
      }
      return false;
    
    case VIM_4:
      if (is_pressed && (get_mods() & MOD_MASK_SHIFT)) { // VIM_$
        // First, temporarily cancelling both shifts so that
        // shift isn't applied to the macro
        del_mods(MOD_MASK_SHIFT);
        switch(VIM_QUEUE) {
          case KC_NO: VIM_END_OF_LINE(); break;
          case VIM_C: VIM_CHANGE_TO_EOL(_BASE); break;
          case VIM_D: VIM_DELETE_TO_EOL(); break;
          case VIM_V: VIM_VISUAL_TO_EOL(); break;
          case VIM_Y: VIM_YANK_TO_EOL(); break;
        }
        // Reapplying modifier state so that the held shift key(s)
        // still work even after VIM_END_OF_LINE() is run
        set_mods(mod_state);
      }
      return false;
    
    case VIM_6:
      if (is_pressed && (get_mods() & MOD_MASK_SHIFT)) { // VIM_^
        del_mods(MOD_MASK_SHIFT);
        switch(VIM_QUEUE) {
          case KC_NO: VIM_START_OF_LINE(); break;
          case VIM_C: VIM_CHANGE_TO_SOL(_BASE); break;
          case VIM_D: VIM_DELETE_TO_SOL(); break;
          case VIM_V: VIM_VISUAL_TO_SOL(); break;
          case VIM_Y: VIM_YANK_TO_SOL(); break;
        }
        set_mods(mod_state);
      }
      return false;
    
    case VIM_A:
      if (is_pressed && (get_mods() & MOD_MASK_SHIFT)) { 
        del_mods(MOD_MASK_SHIFT);
        VIM_APPEND_LINE(_BASE);
        set_mods(mod_state);      
      } else if (is_pressed) {
        VIM_APPEND(_BASE);
      }
      return false;

    case VIM_B:
      if (is_pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: 
            if(get_mods() & MOD_MASK_CTRL) {
              del_mods(MOD_MASK_CTRL);
              PRESS(KC_PGUP);
              set_mods(mod_state);
            } else {
              PRESS(KC_LCTL); 
              PRESS(KC_LEFT);
            }
            break;
          case VIM_C: VIM_CHANGE_BACK(_BASE); break;
          case VIM_D: VIM_DELETE_BACK(); break;
          case VIM_V: VIM_VISUAL_BACK(); break;
        }
      } else {
        RELEASE(KC_PGUP);
        RELEASE(KC_LEFT);
        RELEASE(KC_LCTL);
      }
      return false;

    case VIM_C:
      if (is_pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: 
            if(get_mods() & MOD_MASK_SHIFT) {
              del_mods(MOD_MASK_SHIFT);
              VIM_CHANGE_TO_EOL(_BASE);
              set_mods(mod_state);
            } else {
              VIM_LEADER(VIM_C);
            }
            break;
          case VIM_C: VIM_CHANGE_WHOLE_LINE(_BASE); break;
        }
      }
      return false;

    case VIM_D:
      if (is_pressed) {
        switch(VIM_QUEUE) {
          case KC_NO: 
            if (get_mods() & MOD_MASK_CTRL) {
              VIM_SCROLL_HALF_DOWN();
            } else if (get_mods() & MOD_MASK_SHIFT) {
              del_mods(MOD_MASK_SHIFT);
              VIM_DELETE_TO_EOL();
              set_mods(mod_state);
            } else {
              VIM_LEADER(VIM_D);
            }
            break;
          case VIM_D: VIM_DELETE_WHOLE_LINE(); break;
        }
      }
      return false;

    case VIM_E:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_LCTL); PRESS(KC_RIGHT); break;
          case VIM_C: VIM_CHANGE_END(_BASE); break;
          case VIM_D: VIM_DELETE_END(); break;
          case VIM_V: VIM_VISUAL_END(); break;
          case VIM_Y: VIM_YANK_END(); break;
        }
      } else {
        RELEASE(KC_RIGHT);
        RELEASE(KC_LCTL);
      }
      return false;
    
    case VIM_F:
      if (is_pressed && (get_mods() & MOD_MASK_CTRL)) {
        del_mods(MOD_MASK_CTRL);
        PRESS(KC_PGDN);
        set_mods(mod_state);
      } else {
        RELEASE(KC_PGDN);
      }
      return false;
    
    case VIM_G:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: 
            if (get_mods() & MOD_MASK_SHIFT) {
              del_mods(MOD_MASK_SHIFT);
              VIM_LAST_LINE();
              set_mods(mod_state);
            } else {
              VIM_LEADER(VIM_G);
            }
            break;
          case VIM_G: VIM_FIRST_LINE(); break;
        }
      }
      return false;
    
    case VIM_H:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_LEFT); break;
          case VIM_C: VIM_CHANGE_LEFT(_BASE); break;
          case VIM_D: VIM_DELETE_LEFT(); break;
          case VIM_V: VIM_VISUAL_LEFT(); break;
          case VIM_Y: VIM_YANK_LEFT(); break;
        }
      } else {
        RELEASE(KC_LEFT);
      }
      return false;

    case VIM_I:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: layer_move(_BASE); break;
          case VIM_C: VIM_LEADER(VIM_CI); break;
          case VIM_D: VIM_LEADER(VIM_DI); break;
          case VIM_V: VIM_LEADER(VIM_VI); break;
          case VIM_Y: VIM_LEADER(VIM_YI); break;
        }
      }
      return false;

    case VIM_J:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: 
            if (get_mods() & MOD_MASK_SHIFT) {
              del_mods(MOD_MASK_SHIFT);
              VIM_JOIN();
              set_mods(mod_state);
            } else {
              PRESS(KC_DOWN);
            }
            break;
          case VIM_C: VIM_CHANGE_DOWN(_BASE); break;
          case VIM_D: VIM_DELETE_DOWN(); break;
          case VIM_V: VIM_VISUAL_DOWN(); break;
          case VIM_Y: VIM_YANK_DOWN(); break;
        }
      } else {
        RELEASE(KC_DOWN);
      }
      return false;

    case VIM_K:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_UP); break;
          case VIM_C: VIM_CHANGE_UP(_BASE); break;
          case VIM_D: VIM_DELETE_UP(); break;
          case VIM_V: VIM_VISUAL_UP(); break;
          case VIM_Y: VIM_YANK_UP(); break;
        }
      } else {
        RELEASE(KC_UP);
      }
      return false;

    case VIM_L:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: PRESS(KC_RIGHT); break;
          case VIM_C: VIM_CHANGE_RIGHT(_BASE); break;
          case VIM_D: VIM_DELETE_RIGHT(); break;
          case VIM_V: VIM_VISUAL_RIGHT(); break;
          case VIM_Y: VIM_YANK_RIGHT(); break;
        }
      } else {
        RELEASE(KC_RIGHT);
      }
      return false;

    case VIM_O:
      if (is_pressed) { 
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT); 
          VIM_OPEN_ABOVE(_BASE); 
          set_mods(mod_state);
        } else {
          VIM_OPEN(_BASE); 
        }
      }
      return false;

    case VIM_P:
      if (is_pressed) { 
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT); 
          VIM_PUT_BEFORE(); 
          set_mods(mod_state);
        } else {
          VIM_PUT_AFTER();
        }
      }
      return false;
    
    case VIM_R:
      if (is_pressed) { 
        if (get_mods() & MOD_MASK_CTRL) {
          del_mods(MOD_MASK_SHIFT);
          del_mods(MOD_MASK_CTRL);
          VIM_REDO();
          set_mods(mod_state);
        } else {
          VIM_REPLACE(); 
        }
      }
      return false;

    case VIM_S:
      if (is_pressed) { 
        if (get_mods() & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT); 
          VIM_CHANGE_WHOLE_LINE(_BASE);
          set_mods(mod_state);
        } else {
          VIM_SUBSTITUTE(_BASE);
        }
      }
      return false;

    case VIM_U:
      if (is_pressed) { 
        if (get_mods() & MOD_MASK_CTRL) {
          VIM_SCROLL_HALF_UP();
        } else {
          VIM_UNDO();
        }
      }
      return false;

    case VIM_V:
      if (is_pressed) { VIM_LEADER(VIM_V); }
      return false;

    case VIM_W:
      if (is_pressed) {
        switch (VIM_QUEUE) {
          case KC_NO: VIM_WORD(); break;
          case VIM_C: VIM_CHANGE_WORD(_BASE); break;
          case VIM_CI: VIM_CHANGE_INNER_WORD(_BASE); break;
          case VIM_D: VIM_DELETE_WORD(); break;
          case VIM_DI: VIM_DELETE_INNER_WORD(); break;
          case VIM_V: VIM_VISUAL_WORD(); break;
          case VIM_VI: VIM_VISUAL_INNER_WORD(); break;
          case VIM_Y: VIM_YANK_WORD(); break;
          case VIM_YI: VIM_YANK_INNER_WORD(); break;
        }
      }
      return false;

    case VIM_X:
      if (is_pressed) { 
        switch(VIM_QUEUE) {
          case KC_NO:
            if (get_mods() & MOD_MASK_SHIFT) {
              VIM_DELETE_LEFT();
            } else {
              VIM_DELETE_RIGHT();
            }
            break;
        }
      }
      return false;

    case VIM_Y:
      if (is_pressed) { 
        switch(VIM_QUEUE) {
          case KC_NO:
            if (get_mods() & MOD_MASK_SHIFT) {
              del_mods(MOD_MASK_SHIFT);
              VIM_YANK_TO_EOL();
              set_mods(mod_state);
            } else {
              VIM_LEADER(VIM_Y);
            }
            break;
          case VIM_Y: VIM_YANK_WHOLE_LINE(); break;
        }
      }
      return false;

    default:
      if (is_pressed) { 
        // Clear VIM Leader queue, if non-VIM Keycode sent
        VIM_LEADER(KC_NO);
      }
      return true;
  }
} 

/* Dynamic Tapping Term Config */
#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FT_PSCR:
      return TAPPING_TERM + 40;
#   ifdef TAP_DANCE_ENABLE
    case TD_MINS:
      return TAPPING_TERM + 40;
#   endif // TAP_DANCE_ENABLE
    case RCST_F18:
      return 1;
    case LCS_F18:
      return 1;
    default:
      return TAPPING_TERM;
  }
}
#endif // TAPPING_TERM_PER_KEY

#ifdef RETRO_TAPPING_PER_KEY
bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LCS_F18:
    case RCST_F18:
    case FT_PSCR:
    case FT_BSLS:
    case CO_RCF21:
      return true;
    default:
      return false;
  }
}
#endif // RETRO_TAPPING_PER_KEY

/* Layer State Set */
layer_state_t layer_state_set_user(layer_state_t state) {
  // Tracks the TRANSPARENT and VIM layer state to activate tri-state SYMBOL layer
  state = update_tri_layer_state(state, _TRNS, _VIM, _SYM);

  switch (get_highest_layer(state)) {
    case _SYM:
      clear_mods();
#     ifndef NO_ACTION_ONESHOT
      clear_oneshot_mods();
#     endif  // NO_ACTION_ONESHOT
      break;
    case _TRNS:
      if(previous_layer == _SYM) {
        register_custom_keycode(RCST_F18, 7, 5);
      }
      break;
    case _BASE:
      if(previous_layer == _SYM) {
        unregister_custom_keycode(RCST_F18, 7, 5);
      }
    default:
      break;
  }
  previous_layer = get_highest_layer(state);

  return state;
}

void matrix_init_keymap(void) {
  // debug_enable = true;
};

void matrix_scan_keymap(void) {
}
