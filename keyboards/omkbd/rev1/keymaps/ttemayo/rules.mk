## Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
## SPDX-License-Identifier: GPL-2.0-or-later
## Ergodash/rev1 rules.mk

# QMK Features
BOOTMAGIC_ENABLE = no 		# Bootloader Mode
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no 			# 5192 bytes; Underglow
RGB_MATRIX_ENABLE = no 		# Per-key RGB
TAP_DANCE_ENABLE = no
DYNAMIC_MACRO_ENABLE = no # 726 bytes
LEADER_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMMAND_ENABLE = no 			# Disable to avoid Caps Word Double Shift conflict
MOUSEKEY_ENABLE = yes 		# 600 bytes; Mouse Keycodes
KEY_OVERRIDE_ENABLE = yes	# 990 bytes;

# ttemayo's Custom Features
TTEMAYO_SYM_MACROS_ENABLE = yes
VIMDOWS_ENABLE = yes

# Firmware Size Optimizations
EXTRAFLAGS += -flto
SPACE_CADET_ENABLE = no
BLUETOOTH_ENABLE = no
OLED_DRIVER_ENABLE = no
AUDIO_ENABLE = no
MIDI_ENABLE = no
