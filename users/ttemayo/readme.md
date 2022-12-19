<h1 align="center">ttemayo's Userspace</h1>


# Overview
Hello, I'm @[drashna](https://github.com/drashna)'s biggest fan.

Looking to improve and will continue working on making this userspace more modular, readable, and efficient. Currently, I'm only using this for a single keyboard, but am always open to ideas, suggestions, or help to improve the code!

# Supported Keyboards
### •  [Ergodash](../../keyboards/omkbd/ergodash/rev1/keymaps/ttemayo/README.md) - `omkbd/ergodash/rev1/`

# Layers

|  | **layer_name** |  **Layer**  | **Description**                                                    |
|:-| :------------- |:------------|:------------------------------------------------------------------ |
|0 | `_BASE `       | Base        | QWERTY layout                                                      |
|1 | `_TRNS `       | Transparent | Placeholder layer, used to trigger tri-state Symbol layer          |
|2 | `_FN`          | Function    | Number row replaced with F-keys                                    |
|3 | `_NUM`         | Numpad      | Numpad on right                                                    |
|4 | `_MOUSE`       | Mouse       | Mouse Keys on left                                                 |
|5 | `_VIMTOGGLE`   | VIM Toggle  | Allows VIM bindings in a non-VIM environment                       |
|6 | `_VIM`         | VIM + Media | Similar to above, but with Media keys and without the VIM insert keys (e.g. `a` & `c`) that would move to 'Insert Mode' |
|7 | `_SYM`         | Symbol      | Brackets, Braces, and other annoying symbols and bigrams in macros |

# Features
1. [VIM Emulation](#vimdows)
2. [Tap Dance](#tap-dance)
3. [Physical Key Tracking](#physical-key-tracking) 
4. [Leader Key and Macros](#leader-key-and-macros) 
5. [Autofire Fire Key](#sutofire-fire-key) 
6. [Keycode Aliases and Other](#keycode-aliases-and-other) 
   
## [VIMdows](vimdows.c)
VIM-like emulation (currently working Windows-only): VIMdows lol
- Heavily based on the `ergodox_ez/vim` keymap
- Modified to be more robust, to work with Windows, as well as added additional features, bindings, and functionality
### ❖ Cursor Movement ###
```
h        cursor left
j        cursor down
l        cursor right
k        cursor up
```
```
C-b      Move back one full screen (Page up)
C-f      Move forward one full screen (Page down)
C-d      Mouse scroll down x2 (Actual VIM also moves cursor)
C-u      Mouse scroll up x2 (Actual VIM also moves cursor)
```

```
w        jump to start of next word (punctuation not part of word)
e        jump to end of word (punctuation not part of word)
b        jump to beginning of word (punctuation not part of word)
0        jump to beginning of line
^        jump to the start of line (first non-blank character)
$        jump to the end of line
G        jump to bottom of file
gg       jump to top of file
```
### ❖ Entering Insert Mode ###
```
a        Append text after the cursor
A        Append text at the end of the line
i        Insert text before the cursor
o        Open a new line BELOW the cursor's line
O        Open a new line ABOVE the cursor's line
```
### ❖ Cut, Copy, and Paste ###
#### Delete (Cut) ####
```
x or dl  Delete char UNDER (AFTER) cursor
X or dh  Delete char BEFORE cursor
dj       Delete line under cursor and line BELOW
dk       Delete line under cursor and line ABOVE

dw       Delete to start of next word
de       Delete to end of word
db       Delete to beginning of current word
diw      Delete word under cursor
d^       Delete to the start of the line
D or d$  Delete to the end of the line  
dd       Delete whole line under cursor
```
#### Yank (Copy) ####
```
yl       Yank char UNDER (AFTER) cursor
yh       Yank char BEFORE cursor
yj       Yank line under cursor and line BELOW
yk       Yank line under cursor and line ABOVE

yw       Yank to start of next word
ye       Yank to end of word
yb       Yank to beginning of current word
yiw      Yank word under cursor
y^       Yank to the start of the line
Y or y$  Yank to the end of the line  
yy       Yank whole line under cursor
```
#### Put (Paste) ####
```
p        Put AFTER cursor
P        Put BEFORE (ON) cursor
```
### ❖ Editing ###
```
u        Undo
C-r      Redo
r        Highlight character ON (AFTER) cursor to replace, start insert
J        Joins current line with next line
```
#### Change _(ends in Insert Mode)_ ####
```
s or cl  Delete char UNDER (AFTER) cursor, start insert
ch       Delete char BEFORE cursor, start insert
cj       Delete line under cursor and line BELOW, start insert
ck       Delete line under cursor and line ABOVE, start insert

cw       Delete to start of next word, start insert
ce       Delete to end of current word, start insert
cb       Delete to beginning of current word, start insert
ciw      Delete word under cursor, start insert
c^       Delete to the start of the line, start insert
C or c$  Delete to the end of the line, start insert 
cc or S  Delete whole line under cursor, start insert
```
### ❖ Visual (Marking Text) ###
**Tries to mimmick entering Visual Mode + movement**
```
vl       Select char UNDER (AFTER) cursor
vh       Select char BEFORE cursor
vj       Select line under cursor and line BELOW
vk       Select line under cursor and line ABOVE

vw       Select to start of next word
ve       Select to end of current word
vb       Select to beginning of current word
viw      Select word under cursor
v^       Select to the start of the line
v$       Select to the end of the line
V*       Select whole line under cursor
```
`*` - Unimplemented

## [Tap Dance](tapdance.h)
Previously, I had used tap dance for: 
- `d`  `dd` , single tap _delete_, double tap for _delete line_ 
- `y`  `yy` , single tap _yank_, double tap _yank line_
- `-` `—` , single tap for _hyphen_, double tap for _em dash_
 
Using `cur_dance` to determine Single Tap and Double Tap states:
```java
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) return TD_SINGLE_TAP;
  else if (state->count == 2) return TD_DOUBLE_TAP;
  else return TD_UNKNOWN;
}
```
 
Currently for my Ergodash, Tap Dance functionality is disabled via the flag, `TAP_DANCE_ENABLE` in `rules.mk`.

Check out [DanielGGordon](../gordon/gordon.c)'s examples as well as the documentation for more examples.

## [Conditional Key-override](./ttemayo.c#L9) 
### Modifier Tracking
This is done by tracking the modifier state, which allows us to to trigger different actions and macros depending on what mods are being held down.
Some other interesting ideas include mapping LShift'd RCtrl to send `KC_HOME`, RShift'd LCtrl to send `KC_END`, as well as the "Super F4" example below.

In order to track the physical modifier states, several flags were added:
- **Shift'd state**: `is_shift_pressed`, `is_lshift_pressed`, `is_rshift_pressed`
- **Ctrl'd state**: `is_ctrl_pressed `, `is_lctrl_pressed`, `is_rctrl_pressed`
- **Alt'd state**: `is_alt_pressed`, `is_lalt_pressed`, `is_ralt_pressed`

### Shifted L/RControl
While Mod-tap, Keymap Layers, and Tap Dance can give us plenty of options, this yet another way to give modifier keys additional functionality. By using conditional key-overrides, we gain yet another method of allowing the same modifier key to behave differently, given the condition of the other modifiers (confusing, I know). 

| Modifier        | Tapped Modifier     | Action (when tapped)         
| :-------------- | :------------------ |:--------------------- 
| `None`          | `LCtrl` or `RCtrl`  | `LCtrl` or `RCtrl` respectively
| `KC_LShift`     | `LCtrl`             | `KC_HOME`
| `KC_RShift`     | `RCtrl`             | `KC_END`

### "Super F4"
`F4` is nice to have on base layer for the all-too-familiar `Alt+F4` chord to close out of apps. Having quick access to this is useful to exit-scum games (think _Path of Exile_ or _Diablo_, where you can exit to prevent impending doom). However outside of this, my non-chorded F4 is rarely used.

By checking for the modifiers when chorded, we can make this key multi-purpose.

| Modifier        | Action            
| :-------------- | :-------------- 
| `None`          | `KC_F16` - may be used as a global hotkey for certain applications
| `KC_LShift`     | Move to **Mouse Layer**
| `KC_RShift`     | Move to **Numpad Layer**
| `KC_LAlt`       | Alt + F4

**Implementation:**
```java
// "Super F4"
case KC_F16:
  if(isLAltPressed && record->event.pressed) {
    register_code16(KC_F4);
    unregister_code16(KC_F4);
  } else if (isRShiftPressed && !is_ctrl_pressed && record->event.pressed) {
    if(layer_state_is(_BASE)){
      layer_move(_NUM);
    }
  } else if (is_lshift_pressed && !is_ctrl_pressed && record->event.pressed) {
    if(layer_state_is(_BASE)){
      layer_move(_MOUSE);
    }
  } else if (record->event.pressed) {
    register_code16(KC_F16);
  } else {
    unregister_code16(KC_F16);
  }
  return false;
```

### Encase Cursor on Key Hold
Physical key tracking with [software timers](https://github.com/qmk/qmk_firmware/blob/master/docs/ref_functions.md#software-timers) to encase my cursor upon the key holds:

 The cursor is represented by `¶` here:
| On Tap          | Encase on Hold          | 
| :-------------- | :---------------------- | 
| `/*`**¶**       | `/*`**¶**`*/`           | 
| `*`**¶**        | `*`**¶**`*`             | 
| `%`**¶**        | `%`**¶**`%`             | 
| `` ``` ``**¶**  | `` ``` ``**¶**`` ``` `` | 
| `` ` ``**¶**    | `` ` ``**¶**`` ` ``     | 
| `[`**¶**        | `[`**¶**`]`             | 
| `{`**¶**        | `{`**¶**`}`             | 
| `(`**¶**        | `(`**¶**`)`             | 
| `<`**¶**        | `<`**¶**`>`             | 
| `'`**¶**        | `'`**¶**`'`             | 
| `"`**¶**        | `"`**¶**`"`             | 
| `\|\|`**¶**     | `\|\|`**¶**`\|\|`       | 
| `_`**¶**        | `_`**¶**`_`             | 

#### Implementation:
```java
// globals
bool is_s_cmblk_pressed = false;
uint16_t s_cmblk_timer;
```

```java
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
record->event.pressed;
  switch (keycode) {
    case S_CMBLK:
      if (is_pressed) {
          mod_state = get_mods();
          del_mods(MOD_MASK_CSAG);
          is_s_cmblk_pressed = true;
          s_cmblk_timer = timer_read();
          sym_opencommentblock();
          set_mods(mod_state);
        } else {
          is_s_cmblk_pressed = false;
        }
        return false;
  }
}
```

```java
void matrix_scan_user(void) { 
  if (is_s_cmblk_pressed) {
    if (timer_elapsed(s_cmblk_timer) == TAPPING_TERM + 25) {
      mod_state = get_mods();
      del_mods(MOD_MASK_CSAG);
      SEND_STRING("*/" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
      set_mods(mod_state);
    }
  }
```
  
## [Leader Key and Macros](./ttemayo.c#L302) 
[The Leader Key](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_leader_key.md), `KC_LDR`, is pretty neat. To enable, set `LEADER_ENABLE = yes` in *rules.mk* and `LEADER_EXTERNS();` above your `matrix_scan_user` function.

### CapsLock on Leader Double Tap
Double tapping the Leader Key results in `CapsLock`.
### Selection Encasing Macros
Having macros to wrap your selection with symbols can be useful sometimes outside of an IDE, we call these macros by using the **Leader Key** + a key press.

 The selection is represented by `『』` here:
 |  | Output                    | Description                                       |
 |:-|:------------------------- |:------------------------------------------------  |
 |  | `/* `**『』**` */`        | Wraps selection between block comment markers     |
 |  | `*`**『』**`*`            | Wraps selection between a pair of asterisks       |
 |  | `%`**『』**`%`            | Wraps selection between a pair of percent symbols |
 |  | `` ``` ``**『』**`` ``` ``| Wraps selection between a set of 3 grave ticks (Markdown code block) |
 |  | `` ` ``**『』** `` ` ``   | Wraps selection between a set of grave symbols    |
 |  | `[`**『』**`]`            | Wraps selection between a pair of square brackets |
 |  | `{`**『』**`}`            | Wraps selection between a pair of curly braces    |
 |  | `(`**『』**`)`            | Wraps selection between a pair of parenthesis     |
 |  | `<`**『』**`>`            | Wraps selection between a pair of angle brackets  |


## Autofire Fire Key
### Autoclicker
Custom keycode to rapid fire Mouse Button 1 while held.

**Note: Not added, since it would probably be better to do this at the true software level**


#### Implementation:
```java
enum custom_keycodes {
  RAPID_FIRE
};
```

```java
bool rapidFireOn = false; // global
```

```java
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RAPID_FIRE:
      if (record->event.pressed) {
        rapidFireOn = true;
      } else {
        rapidFireOn = false;
      }
      break;
  }
  return true;
}
```

```java
void matrix_scan_user(void) {
  if (rapidFireOn) {
    tap_code(KC_MS_BTN1);
  }
}
```

## Keycode Aliases and Other
### Momentary Layer-Tap
| Alias                | Keycode              | Action                                                     |
| :------------------- | :------------------- |:---------------------------------------------------------- |
| **`FT_PSCR`**        | `LT(_FN,KC_PSCR)`    | **_Function Layer_** on hold, Print Screen on tap          | 
| **`FT_BSLS`**        | `LT(_FN,KC_BSLS)`    | **_Function Layer_** on hold, Backslash on tap             |

### Modified Momentary Layer-Tap
| Alias                | Keycode              | Action                                                     |
| :------------------- | :------------------- |:---------------------------------------------------------- |
| **`LT_VIM`**         | `LTTO_VIM`           | **_VIM + Media Layer_** on hold, **_VIM Toggle Layer_** on `RCtrl` + tap |
| **`MPRV_RW`**        | `LT(0, KC_MPRV)`     | Rewind on hold, Media Previous Track on tap                |
| **`MNXT_FF`**        | `LT(0, KC_MNXT)`     | FastForward on hold, Media Next Track on tap               |
| **`RCST_F18`**       | `LT(1, KC_F18)`      | **_Transparent Layer_**  + Right Control and Shift on hold, F18 of tap |

### Mod-Tap
| Alias                | Keycode              | Action                                                     |
| :------------------- | :------------------- |:---------------------------------------------------------- |
| **`MEH_F17`**        | `MEH_T(KC_F17)`      | Left Control, Shift, and Alt on hold, F17 on tap           |
| **`LCS_F18`**        | `C_S_T(KC_F18)`      | Left Control and Shift on hold, F18 on tap                 |
| **`ALL_EMD`**        | `HYPR_T(EMDASH) `    | Left Control, Shift, Alt, and GUI on hold, Em Dash on tap  |

### Chord Abbreviations
| Alias                | Keycode              | Action                                                     |
| :------------------- | :------------------- |:---------------------------------------------------------- |
| **`CTLC`**           | `LCtrl+C`            | LCtrl + C                                                  |
| **`CTLX`**           | `LCtrl+X`            | LCtrl + X                                                  |
| **`CTLF`**           | `LCtrl+F`            | LCtrl + F                                                  |


## To do
- [ ] Move 'Layers' section to keymap's readme.md
- [ ] Add **Dynamic Macros**
  - [ ] Use `Scroll Lock` LED/state to track Dynamic Recording state (?)
- [ ] Remove unused `Hypr(EMDASH)` (Modified Tap part of Mod-Tap) from keymap
- [ ] Refactor Custom Features into seperate files(?)
- [ ] (Overload) functions to minimize disable/enable mods: `no_mod_tap_code()`, `no_mod_send_string()`(?):
  -  could be similar to _custom_keycode.h_
```java
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool is_pressed = record->event.pressed;
  switch (keycode) {
    case S_ASTR:
      if (is_pressed) {
          mod_state = get_mods();
          del_mods(MOD_MASK_CSAG);
          is_s_astr_pressed = true;
          s_astr_timer = timer_read();
          tap_code16(KC_ASTR);
          set_mods(mod_state);
        } else {
          is_s_astr_pressed = false;
        }
        return false;
  }
  ...
```
```java
void matrix_scan_user(void) { 
  if (is_s_astr_pressed) {
      if (timer_elapsed(s_astr_timer) == TAPPING_TERM + 25) {
        mod_state = get_mods();
        del_mods(MOD_MASK_CSAG);
        SEND_STRING("*" SS_TAP(X_LEFT));
        set_mods(mod_state);
      }
    }
    ...
```

#### Other Notes
Rows are doubled up instead of columns due to the way the keyboard matrix is scanned. It scans one row at a time. What the slave does it scan its rows and passes it to the master. The master then stores all the row data together by virtually stacking the rows of the left half on top of the right half.
A macro remaps the stacked rows to the correct layout later on.

# License
Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

<h4 align="center">🚧</h4>