// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include QMK_KEYBOARD_H
#include "print.h"
#include "quantum.h"
#include "quantum_keycodes.h"

/* VIM Definitions */
int _VIM_INSERT_LAYER;

enum vim_custom_keycodes {
  VIM_PLACEHOLDER = SAFE_RANGE,
  VIM_ESC,
  LTTO_VIM,
  VIM_0,
  VIM_4, // `$`
  VIM_6, // `^`  
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_F,
  VIM_G,
  VIM_H,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_R,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  VIM_YI,
  VIM_SAFE_RANGE, // SAFE_RANGE+33
};

#define LT_VIM   LTTO_VIM

uint16_t VIM_QUEUE;
uint16_t ltto_vim_timer;

void VIM_LEFT(void); 
void VIM_DOWN(void);
void VIM_UP(void);
void VIM_RIGHT(void); 
void VIM_BEGINNING(void);
void VIM_WORD(void);
void VIM_END(void);
void VIM_START_OF_LINE(void);
void VIM_BEGINNING_OF_LINE(void);
void VIM_END_OF_LINE(void);

void VIM_SCROLL_HALF_DOWN(void);
void VIM_SCROLL_HALF_UP(void);
void VIM_SCROLL_FULL_FORWARD(void);
void VIM_SCROLL_FULL_BACK(void);
void VIM_FIRST_LINE(void);
void VIM_LAST_LINE(void);

void VIM_APPEND(int insert_layer);
void VIM_APPEND_LINE(int insert_layer);
void VIM_CHANGE_BACK(int insert_layer);
void VIM_CHANGE_DOWN(int insert_layer);
void VIM_CHANGE_END(int insert_layer);
void VIM_CHANGE_INNER_WORD(int insert_layer);
void VIM_CHANGE_LEFT(int insert_layer);
void VIM_CHANGE_TO_EOL(int insert_layer);
void VIM_CHANGE_TO_SOL(int insert_layer);
void VIM_CHANGE_RIGHT(int insert_layer);
void VIM_CHANGE_UP(int insert_layer);
void VIM_CHANGE_WHOLE_LINE(int insert_layer);
void VIM_CHANGE_WORD(int insert_layer);
void VIM_DELETE_BACK(void);
void VIM_DELETE_DOWN(void);
void VIM_DELETE_END(void);
void VIM_DELETE_INNER_WORD(void);
void VIM_DELETE_LEFT(void);
void VIM_DELETE_TO_EOL(void);
void VIM_DELETE_TO_SOL(void);
void VIM_DELETE_RIGHT(void);
void VIM_DELETE_UP(void);
void VIM_DELETE_WHOLE_LINE(void);
void VIM_DELETE_WORD(void);
void VIM_JOIN(void);
void VIM_OPEN(int insert_layer);
void VIM_OPEN_ABOVE(int insert_layer);
void VIM_PUT_AFTER(void); 
void VIM_PUT_BEFORE(void);
void VIM_REDO(void);
void VIM_REPLACE(void);
void VIM_SUBSTITUTE(int insert_layer);
void VIM_UNDO(void);
void VIM_VISUAL_BACK(void);
void VIM_VISUAL_DOWN(void);
void VIM_VISUAL_END(void);
void VIM_VISUAL_INNER_WORD(void);
void VIM_VISUAL_LEFT(void);
void VIM_VISUAL_TO_SOL(void);
void VIM_VISUAL_TO_EOL(void);
void VIM_VISUAL_RIGHT(void);
void VIM_VISUAL_UP(void);
void VIM_VISUAL_WORD(void);
void VIM_YANK_BACK(void);
void VIM_YANK_DOWN(void);
void VIM_YANK_END(void);
void VIM_YANK_INNER_WORD(void);
void VIM_YANK_LEFT(void);
void VIM_YANK_TO_SOL(void);
void VIM_YANK_TO_EOL(void);
void VIM_YANK_RIGHT(void);
void VIM_YANK_UP(void);
void VIM_YANK_WHOLE_LINE(void);
void VIM_YANK_WORD(void);

void VIM_LEADER(uint16_t keycode);

/* Helper functions */
#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
void TAP(uint16_t keycode);
void CMD(uint16_t keycode);
void CTRL(uint16_t keycode);
void SHIFT(uint16_t keycode);
void ALT(uint16_t keycode);
