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
#include QMK_KEYBOARD_H

enum layer_names {
  BASE = 0,
  OTHER
};

enum custom_keycodes{
  KC_DRGSCRL = PLOOPY_SAFE_RANGE, // safe range starts at `PLOOPY_SAFE_RANGE` instead.
  LT_BTN5,
  LYR_BTN5
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT( /* Base */
        KC_BTN1, KC_BTN3, KC_BTN4,
          KC_BTN2, DRAG_SCROLL
    ),
    [OTHER] = LAYOUT(
        _______, _______, _______,
          _______, _______
    )
};

