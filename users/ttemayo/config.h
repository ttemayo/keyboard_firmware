// Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Mouse Key Mode and config */
#ifdef MOUSEKEY_ENABLE
#  define MK_COMBINED /* Holding movement keys accelerates the cursor until it reaches 
                          its maximum speed, but holding acceleration and movement keys 
                          simultaneously moves the cursor at constant speeds. */
#endif // MOUSEKEY_ENABLE

#ifdef CAPS_WORD_ENABLE
#  define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#  define CAPS_WORD_IDLE_TIMEOUT 5000 // 5 seconds (default).
#endif // CAPS_WORD_ENABLE
