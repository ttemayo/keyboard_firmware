// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "vimdows.h"

uint16_t VIM_QUEUE = KC_NO;

int _VIM_INSERT_LAYER = 0; // Defaults bottom-most layer, 0

__attribute__((weak)) void matrix_init_keymap(void) {} // Possibly move to <name>.c?

/* Call user matrix init before calling the keymap's init function */
void matrix_init_user(void) {
  VIM_LEADER(KC_NO);
  matrix_init_keymap(); 
}

/**
 * Sets the `VIM_QUEUE` variable to the incoming keycode.
 * Pass `KC_NO` to cancel the operation.
 * @param keycode
 */
void VIM_LEADER(uint16_t keycode) {
  VIM_QUEUE = keycode;
  switch(keycode) {
    case VIM_C: print("\e[32mc\e[0m"); break;
    case VIM_CI: print("\e[32mci\e[0m"); break;
    case VIM_D: print("\e[32md\e[0m"); break;
    case VIM_DI: print("\e[32mdi\e[0m"); break;
    case VIM_G: print("\e[32mg\e[0m"); break;
    case VIM_R: print("\e[32mr\e[0m"); break;
    case VIM_V: print("\e[32mv\e[0m"); break;
    case VIM_VI: print("\e[32mvi\e[0m"); break;
    case VIM_Y: print("\e[32my\e[0m"); break;
    case VIM_YI: print("\e[32myi\e[0m"); break;
    case KC_NO: print("❎"); break;
  }
}

/**
 * Keycode Helper Functions
 * Can help with function reability
 * @param keycode
 */
void TAP(uint16_t keycode) {
  PRESS(keycode);
  RELEASE(keycode);
}

void CMD(uint16_t keycode) {
  PRESS(KC_LGUI);
    TAP(keycode);
  RELEASE(KC_LGUI);
}

void CTRL(uint16_t keycode) {
  PRESS(KC_LCTL);
    TAP(keycode);
  RELEASE(KC_LCTL);
}

void SHIFT(uint16_t keycode) {
  PRESS(KC_LSFT);
    TAP(keycode);
  RELEASE(KC_LSFT);
}

void ALT(uint16_t keycode) {
  PRESS(KC_LALT);
    TAP(keycode);
  RELEASE(KC_LALT);
}

 /* VIM, WINDOWS Implementation */
/***
 *       ####  #    # ######     ####  #    #  ####  ##### 
 *      #    # ##   # #         #      #    # #    #   #   
 *      #    # # #  # #####      ####  ###### #    #   #   
 *      #    # #  # # #              # #    # #    #   #   
 *      #    # #   ## #         #    # #    # #    #   #   
 *       ####  #    # ######     ####  #    #  ####    #   
 */
 
/**
 * Vim-like `move to beginning of line` command.
 * `0` sends Home, Home
 */
 void VIM_BEGINNING_OF_LINE(void) {
  print("\e[31m0\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
 }

/**
 * Vim-like `append` command
 * `a` sends →
 * and then moves to the Insert Layer
 */
void VIM_APPEND(int insert_layer) {
  print("\e[31ma\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_RIGHT);
  layer_move(insert_layer);
}

/**
 * Vim-like `beginning of word` command
 * `b` sends Ctrl + ←
 */
void VIM_BEGINNING(void) {
  print("\e[31mb\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_LEFT);
}

/**
 * Vim-like `end of word` command
 * `e` sends Ctrl + →
 */
void VIM_END(void) {
  print("\e[31me\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_RIGHT);
}

/**
 * Vim-like `left` command
 * `h` sends ←
 */
void VIM_LEFT(void) {
  print("\e[31mh\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_LEFT);
}

/**
 * Vim-like `down` command
 * `j` sends ↓
 */
void VIM_DOWN(void) {
  print("\e[31mj\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_DOWN);
}

/**
 * Vim-like `up` command
 * `k` sends ↑
 */
void VIM_UP(void) {
  print("\e[31mk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_UP);
}

/**
 * Vim-like `right` command
 * `l` sends →
 */
void VIM_RIGHT(void) {
  print("\e[31ml\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_RIGHT);
}

/**
 * Vim-like `open` command
 * `o` sends `End` to move to the end of the line, `Enter` to open a new line,
 * and then moves to the Insert Layer
 */
void VIM_OPEN(int insert_layer) {
  print("\e[31mo\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  TAP(KC_ENTER);
  layer_move(insert_layer);
}

/**
 * Vim-like `put after` command
 * `p` sends → then Ctrl + v (paste)
 */
void VIM_PUT_AFTER(void) {
  print("\e[31mp\e[0m");
  VIM_LEADER(KC_NO);
  VIM_RIGHT();
  CTRL(KC_V);
}

/**
 * Vim-like `replace`
 * `r` sends ⇧→ to select a character
 */
void VIM_REPLACE(void){
  print("\e[31mr\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
}

/**
 * Vim-like `substitute` command
 * `s` sends ⇧→ to select the next character, Ctrl + x (cut)
 * and then moves to the Insert Layer
 */
void VIM_SUBSTITUTE(int insert_layer) {
  print("\e[31ms\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CTRL(KC_X);
  layer_move(insert_layer);
}

/**
 * Vim-like `undo` command
 * `u` sends Ctrl + z
 */
void VIM_UNDO(void) {
  print("\e[31mu\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_Z);
}

/**
 * Vim-like `start of next word` command
 * `w` sends Ctrl + →→←
 */
void VIM_WORD(void) { // gets caught on some strings with special characters
  print("\e[31mw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    TAP(KC_RIGHT);
    TAP(KC_RIGHT);
    TAP(KC_LEFT);
  RELEASE(KC_LCTL);
}

/***
 *       ####  #    # # ###### ##### ###### #####  
 *      #      #    # # #        #   #      #    # 
 *       ####  ###### # #####    #   #####  #    # 
 *           # #    # # #        #   #      #    # 
 *      #    # #    # # #        #   #      #    # 
 *       ####  #    # # #        #   ###### ##### 
 */

 /**
 * Vim-like 'jump to end of line' command
 * `$` sends End
 */
void VIM_END_OF_LINE(void) {
  print("\e[31m$\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
}

/**
 * Vim-like 'jump to start (past spaces) of line' command
 * `^` sends End, then Home
 */
void VIM_START_OF_LINE(void) {
  print("\e[31m^\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  TAP(KC_HOME);
}

/**
 * Vim-like `append to line` command
 * `A` sends End 
 * and then moves to the Insert Layer
 */
void VIM_APPEND_LINE(int insert_layer) {
  print("\e[31mA\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  layer_move(insert_layer);
}

/**
 * Vim-like `change to end of line` command
 * `C` aka `c$` sends ⇧End, then Ctrl + x
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_TO_EOL(int insert_layer) {
  print("\e[31mC\e[0m");
  VIM_LEADER(KC_NO);
  VIM_DELETE_TO_EOL();
  layer_move(insert_layer);
}

/**
 * Vim-like 'delete to end of line' command
 * `D` sends ⇧End, then Ctrl + X
 */
void VIM_DELETE_TO_EOL(void) {
  print("\e[31mD\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_END);
  CTRL(KC_X);
}

/**
 * Vim-like 'jump to last line' command
 * `G` sends Ctrl + End
 */
void VIM_LAST_LINE(void) {
  print("\e[31mG\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_END);
}

/**
 * Vim-like 'join lines' command
 * `J` sends END, then DELETE
 */
void VIM_JOIN(void) {
  print("\e[31mJ\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  TAP(KC_DELETE);
  VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'open above' command
 * `O` sends `Home`,`Enter`, ↑ to move up to the new line, 
 * and then moves to the Insert Layer
 */
void VIM_OPEN_ABOVE(int insert_layer) {
  print("\e[31mO\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_ENTER);
  TAP(KC_UP);
  layer_move(insert_layer);
}

/**
 * Vim-like `put before` command
 * `P` sends Ctrl + v (paste)
 */
void VIM_PUT_BEFORE(void) {
  print("\e[31mP\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_V);
}

/**
 * Vim-like 'change whole line' command
 * `S` aka `cc` sends ⇧HOME,HOME
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_WHOLE_LINE(int insert_layer) {
  print("\e[31mS\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  PRESS(KC_LSFT);
    TAP(KC_END);
    TAP(KC_RIGHT);
  RELEASE(KC_LSFT);
  CTRL(KC_X);
  layer_move(insert_layer);
}

/**
 * Vim-like `yank to end of line` command
 * `Y` aka `y$` sends ⇧End, Ctrl + c, then sets the cursor back
 */
void VIM_YANK_TO_EOL(void) {
  print("\e[31mY\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_END);
  CTRL(KC_C);
  TAP(KC_LEFT);
}

/***
 *       ####  ##### #####  #      ###### #####  
 *      #    #   #   #    # #      #      #    # 
 *      #        #   #    # #      #####  #    # 
 *      #        #   #####  #      #      #    # 
 *      #    #   #   #   #  #      #      #    # 
 *       ####    #   #    # ###### ###### #####  
 */

/**
 * Vim-like `redo` command
 * `C-r` sends Ctrl+y
 */
void VIM_REDO(void) {
  print("\e[31mC-r\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_Y);
}

/**
 * Vim-like `scroll down half page` 
 * `C-d` sends Mouse Scroll Down, Mouse Scroll Down
 */ 
void VIM_SCROLL_HALF_DOWN(void) {
  print("\e[31mC-d\e[0m");
  VIM_LEADER(KC_NO);
  //del_mods(MOD_MASK_CTRL); not working as I understand it
  unregister_mods(MOD_MASK_CTRL);
  TAP(KC_MS_WH_DOWN);
  TAP(KC_MS_WH_DOWN);
} 

/**
 * Vim-like `scroll up half page` 
 * `C-u` sends Mouse Scroll Up, Mouse Scroll Up
 */ 
void VIM_SCROLL_HALF_UP(void) {
  print("\e[31mC-u\e[0m");
  VIM_LEADER(KC_NO);
  unregister_mods(MOD_MASK_CTRL);
  TAP(KC_MS_WH_UP);
  TAP(KC_MS_WH_UP);
  }

/**
 * Vim-like `scroll forward full page` 
 * `C-f` sends Page Down
 */ 
void VIM_SCROLL_FULL_FORWARD(void) {
  print("\e[31mC-f\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_PGDN);
}

/**
 * Vim-like `scroll back full page` 
 * `C-b` sends Page Up
 */ 
void VIM_SCROLL_FULL_BACK(void) {
  print("\e[31mC-b\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_PGUP);
}
 
 /***
 *       ####     #####  #####  ###### ###### # #    # 
 *      #    #    #    # #    # #      #      #  #  #  
 *      #         #    # #    # #####  #####  #   ##   
 *      #  ###    #####  #####  #      #      #   ##   
 *      #    #    #      #   #  #      #      #  #  #  
 *       ####     #      #    # ###### #      # #    # 
 */

/**
 * Vim-like 'jump to first line' command
 * `gg` sends Ctrl + Home
 */
void VIM_FIRST_LINE(void) {
  print("\e[31mgg\e[0m");
  VIM_LEADER(KC_NO);
  CTRL(KC_HOME);
}

/***
 *      #   #    #####  #####  ###### ###### # #    # 
 *       # #     #    # #    # #      #      #  #  #  
 *        #      #    # #    # #####  #####  #   ##   
 *        #      #####  #####  #      #      #   ##   
 *        #      #      #   #  #      #      #  #  #  
 *        #      #      #    # ###### #      # #    # 
 */

/**
 * Vim-like `yank to start of line` command
 * `y^` sends ⇧HOME, Ctrl + c, then sets the cursor back
 */
void VIM_YANK_TO_SOL(void) {
  print("\e[31my^\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_HOME);
  CTRL(KC_C);
  TAP(KC_RIGHT);
}

/**
 * Vim-like `yank back` 
 * `yb` command sends Ctrl + SHIFT + LEFT DEL
 */
void VIM_YANK_BACK(void) {
  print("\e[31myb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_LEFT); // select to start of word
    TAP(KC_C);  // yank selection
  RELEASE(KC_LCTL);
  TAP(KC_RIGHT);  // return cursor
}

/**
 * Vim-like `yank to end of word` 
 * `ye` sends Ctrl + ⇧→ , Ctrl + c
 */
void VIM_YANK_END(void) {
  print("\e[31mye\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT);  // select to end of this word
  RELEASE(KC_LCTL);
  CTRL(KC_C);
  TAP(KC_LEFT); // return cursor
}

/**
 * Vim-like `yank left` 
 * `yh` sends ⇧←, Ctrl + c
 */
void VIM_YANK_LEFT(void) {
  print("\e[31myh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
  CTRL(KC_C);
  TAP(KC_RIGHT); // return cursor
}

/**
 * Vim-like `yank down` 
 * `yj` sends HOME, HOME, ⇧↓END→, then Ctrl + c, returns cursor back to original line
 */
void VIM_YANK_DOWN(void) {
  print("\e[31myj\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  PRESS(KC_LSFT);
    TAP(KC_DOWN);
    TAP(KC_END);
    TAP(KC_RIGHT);
  RELEASE(KC_LSFT);
  CTRL(KC_C);
  TAP(KC_UP);
  TAP(KC_UP);
}

/**
 * Vim-like `yank up` 
 * `yk` sends END, ⇧↑HOMEHOME←, then Ctrl + c, returns cursor back to original line
 */
void VIM_YANK_UP(void) {
  print("\e[31myk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  PRESS(KC_LSFT);
    TAP(KC_UP);
    TAP(KC_HOME);
    TAP(KC_HOME);
    TAP(KC_LEFT);
  RELEASE(KC_LSFT);
  CTRL(KC_C);
  TAP(KC_DOWN);
  TAP(KC_DOWN);
}

/**
 * Vim-like `yank right` 
 * `yl` sends ⇧→, Ctrl + c
 */
void VIM_YANK_RIGHT(void) {
  print("\e[31myl\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CTRL(KC_C);
  TAP(KC_LEFT); // return cursor
}

/**
 * Vim-like `yank start of next word` 
 * `yw` sends Ctrl + ⇧→→←, Ctrl + c
 */
void VIM_YANK_WORD(void) {
  print("\e[31myw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT);  // select to end of this word
    SHIFT(KC_RIGHT);  // select to end of next word
    SHIFT(KC_LEFT);   // select to start of next word
  RELEASE(KC_LCTL);
  CTRL(KC_C);   // yank selection
  TAP(KC_LEFT); // return cursor
}

/**
 * Vim-like `yank whole line` 
 * `yy`sends Home, Home, Shift End Ctrl + c
 */
void VIM_YANK_WHOLE_LINE(void) {
  print("\e[31myy\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  PRESS(KC_LSFT);
    TAP(KC_END);
    TAP(KC_RIGHT);
  RELEASE(KC_LSFT);
  CTRL(KC_C);
  TAP(KC_LEFT); // return cursor
}

/***
 *      #   # #    #####  #####  ###### ###### # #    # 
 *       # #  #    #    # #    # #      #      #  #  #  
 *        #   #    #    # #    # #####  #####  #   ##   
 *        #   #    #####  #####  #      #      #   ##   
 *        #   #    #      #   #  #      #      #  #  #  
 *        #   #    #      #    # ###### #      # #    # 
 *                                                      
 */

/**
 * Vim-like `yank inner word` 
 * `yiw` moves back then copies to the end of the word
 */
void VIM_YANK_INNER_WORD(void) {
  print("\e[31myiw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BEGINNING();
  VIM_YANK_END();
}

/***
*       #####      #####  #####  ###### ###### # #    # 
*       #    #     #    # #    # #      #      #  #  #  
*       #    #     #    # #    # #####  #####  #   ##   
*       #    #     #####  #####  #      #      #   ##   
*       #    #     #      #   #  #      #      #  #  #  
*       #####      #      #    # ###### #      # #    #
*/

/**
 * Vim-like `delete to start of line` command
 * `d^` sends ⇧HOME, then Ctrl + x
 */
void VIM_DELETE_TO_SOL(void){
  print("\e[31md^\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_HOME);
  CTRL(KC_X);
}

/**
 * Vim-like `delete beginning of word` command
 * `db` selects to the end of the word then cuts
 */
void VIM_DELETE_BACK(void) {
  print("\e[31mdb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_LEFT); // select to start of word
  RELEASE(KC_LCTL);
  CTRL(KC_X);
}

/**
 * Vim-like `delete whole line` command
 * `dd` sends `Home` to move to start of line,
 * selecting the whole line, then sending Ctrl + x to cut the line
 */
void VIM_DELETE_WHOLE_LINE(void) {
  print("\e[31mdd\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  PRESS(KC_LSFT);
    TAP(KC_END);
    TAP(KC_RIGHT);
  RELEASE(KC_LSFT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete end of word` command
 * `de` sends Ctrl + ⇧→ then Ctrl + x
 */
void VIM_DELETE_END(void) {
  print("\e[31mde\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT); // select to end of this word
  RELEASE(KC_LCTL);
  CTRL(KC_X);
}

/**
 * Vim-like `delete left` command
 * `dh` aka `X` sends ⇧← then Ctrl + x
 */
void VIM_DELETE_LEFT(void) {
  print("\e[31mdh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete down` command
 * `dj` sends HOME, HOME, ⇧↓END→, then Ctrl + x
 */
void VIM_DELETE_DOWN(void) {
  print("\e[31mdj\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_HOME);
  TAP(KC_HOME);
  PRESS(KC_LSFT);
    TAP(KC_DOWN);
    TAP(KC_END);
    TAP(KC_RIGHT);
  RELEASE(KC_LSFT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete up` command
 * `dk` sends END, ⇧↑HOMEHOME←, then Ctrl + x
 */
void VIM_DELETE_UP(void) {
  print("\e[31mdk\e[0m");
  VIM_LEADER(KC_NO);
  TAP(KC_END);
  PRESS(KC_LSFT);
    TAP(KC_UP);
    TAP(KC_HOME);
    TAP(KC_HOME);
    TAP(KC_LEFT);
  RELEASE(KC_LSFT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete right` command
 * `dl` aka `x` sends ⇧→ then Ctrl + x
 */
void VIM_DELETE_RIGHT(void) {
  print("\e[31mdl\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
  CTRL(KC_X);
}

/**
 * Vim-like `delete start of next word` command
 * `dw` sends Ctrl + ⇧→→← then Ctrl + x to select to the start
 * of the next word then cut
 */
void VIM_DELETE_WORD(void) {
  print("\e[31mdw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT);  // select to end of this word
    SHIFT(KC_RIGHT);  // select to end of next word
    SHIFT(KC_LEFT);   // select to start of next word
  RELEASE(KC_LCTL);
  CTRL(KC_X); // delete selection
}

/***
*       #####  #    #####  #####  ###### ###### # #    # 
*       #    # #    #    # #    # #      #      #  #  #  
*       #    # #    #    # #    # #####  #####  #   ##   
*       #    # #    #####  #####  #      #      #   ##   
*       #    # #    #      #   #  #      #      #  #  #  
*       #####  #    #      #    # ###### #      # #    #
*/

/**
 * Vim-like `delete inner word` command
 * `diw` send back then cuts to the end of the word
 */
void VIM_DELETE_INNER_WORD(void) {
  print("\e[31mdiw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BEGINNING();
  VIM_DELETE_END();
}

/***
*        ####     #####  #####  ###### ###### # #    # 
*       #    #    #    # #    # #      #      #  #  #  
*       #         #    # #    # #####  #####  #   ##   
*       #         #####  #####  #      #      #   ##   
*       #    #    #      #   #  #      #      #  #  #  
*        ####     #      #    # ###### #      # #    # 
*/

/**
 * Vim-like `change to start of line` command
 * `c^` sends ⇧HOME, then Ctrl + x
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_TO_SOL(int insert_layer){
  print("\e[31mc^\e[0m");
  VIM_DELETE_TO_SOL();
  layer_move(insert_layer);
}

/**
 * Vim-like `change beginning of word` command
 * `cb` deletes to the start of the word,
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_BACK(int insert_layer) {
  print("\e[31mcb\e[0m");
  VIM_DELETE_BACK();
  layer_move(insert_layer);
}

/**
 * Vim-like `change end of word` command
 * `ce` deletes to the end of the word,
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_END(int insert_layer) {
  print("\e[31mce\e[0m");
  VIM_DELETE_END();
  layer_move(insert_layer);
}

/**
 * Vim-like `change left` command
 * `ch` aka `r` deletes one character left
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_LEFT(int insert_layer) {
  print("\e[31mch\e[0m");
  VIM_DELETE_LEFT();
  layer_move(insert_layer);
}

/**
 * Vim-like `change down` command
 * `cj` sends HOME, HOME, ⇧↓END→, then Ctrl + x
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_DOWN(int insert_layer) {
  print("\e[31mcj\e[0m");
  VIM_DELETE_DOWN();
  layer_move(insert_layer);
}

/**
 * Vim-like `change up` command
 * `ck` sends END, ⇧↑HOMEHOME←, then Ctrl + x
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_UP(int insert_layer) {
  print("\e[31mck\e[0m");
  VIM_DELETE_UP();
  layer_move(insert_layer);
}

/**
 * Vim-like `change right` command
 * `cl` aka `s` deletes one character right
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_RIGHT(int insert_layer) {
  print("\e[31mcl\e[0m");
  VIM_DELETE_RIGHT();
  layer_move(insert_layer);
}

/**
 * Vim-like `change to start of next word` command
 * `cw` command by first deleting to the end of the word,
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_WORD(int insert_layer) {
  print("\e[31mcw\e[0m");
  VIM_DELETE_WORD();
  layer_move(insert_layer);
}

/***
*        ####  #   #####  #####  ###### ###### # #    # 
*       #    # #   #    # #    # #      #      #  #  #  
*       #      #   #    # #    # #####  #####  #   ##   
*       #      #   #####  #####  #      #      #   ##   
*       #    # #   #      #   #  #      #      #  #  #  
*        ####  #   #      #    # ###### #      # #    # 
*/

/**
 * Vim-like `change inner word` command
 * `ciw` command by deleting the inner word
 * and then moves to the Insert Layer
 */
void VIM_CHANGE_INNER_WORD(int insert_layer) {
  print("\e[31mciw\e[0m");
  VIM_DELETE_INNER_WORD();
  layer_move(insert_layer);
}

/***
 *      #    #     #####  #####  ###### ###### # #    # 
 *      #    #     #    # #    # #      #      #  #  #  
 *      #    #     #    # #    # #####  #####  #   ##   
 *      #    #     #####  #####  #      #      #   ##   
 *       #  #      #      #   #  #      #      #  #  #  
 *        ##       #      #    # ###### #      # #    # 
 */

/**
 * Vim-like `Visual Mode select to end of line` command
 * `v$` selects to the end of line
 */
void VIM_VISUAL_TO_EOL(void) {
  print("\e[31mv$\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_END);
}

/**
 * Vim-like `Visual Mode select to start of line` command
 * `v^` selects to the start of line
 */
void VIM_VISUAL_TO_SOL(void){
  print("\e[31mv^\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_HOME);
}

/**
 * Vim-like `Visual Mode select beginning of word` command
 * `vb` selects to the beginning of the word
 */
void VIM_VISUAL_BACK(void) {
  print("\e[31mvb\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_LEFT); // select to start of word
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `Visual Mode select end of word` command
 * `ve` selects to the end of the word.
 */
void VIM_VISUAL_END(void) {
  print("\e[31mve\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT);  // select to end of this word
  RELEASE(KC_LCTL);
}

/**
 * Vim-like `Visual Mode select left` command
 * `vh` sends ⇧←.
 */
void VIM_VISUAL_LEFT(void) {
  print("\e[31mvh\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_LEFT);
}

/**
 * Vim-like `Visual Mode select down` command
 * `vj` sends ⇧↓.
 */
void VIM_VISUAL_DOWN(void) {
  print("\e[31mvj\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_DOWN);
}

/**
 * Vim-like `Visual Mode select up` command
 * `vk` sends ⇧↑.
 */
void VIM_VISUAL_UP(void) {
  print("\e[31mvk\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_UP);
}

/**
 * Vim-like `Visual Mode select right` command
 * `vl` sends ⇧→.
 */
void VIM_VISUAL_RIGHT(void) {
  print("\e[31mvl\e[0m");
  VIM_LEADER(KC_NO);
  SHIFT(KC_RIGHT);
}

/**
 * Vim-like `Visual Mode select to start of next word` command
 * `vw` selects to the beginning of the next word.
 */
void VIM_VISUAL_WORD(void) {
  print("\e[31mvw\e[0m");
  VIM_LEADER(KC_NO);
  PRESS(KC_LCTL);
    SHIFT(KC_RIGHT);  // select to end of this word
    SHIFT(KC_RIGHT);  // select to end of next word
    SHIFT(KC_LEFT);   // select to start of next word
  RELEASE(KC_LCTL);
}

/***
 *      #    # #    #####  #####  ###### ###### # #    # 
 *      #    # #    #    # #    # #      #      #  #  #  
 *      #    # #    #    # #    # #####  #####  #   ##   
 *      #    # #    #####  #####  #      #      #   ##   
 *       #  #  #    #      #   #  #      #      #  #  #  
 *        ##   #    #      #    # ###### #      # #    # 
 */
 
/**
 * Vim-like `Visual Mode select inner word` command
 * `viw` command by moving back then selecting to the end of the word.
 */
void VIM_VISUAL_INNER_WORD(void) {
  print("\e[31mviw\e[0m");
  VIM_LEADER(KC_NO);
  VIM_BEGINNING();
  VIM_VISUAL_END();
}
