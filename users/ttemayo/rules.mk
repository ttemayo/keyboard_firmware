## Copyright 2022 Kevin Hoang (@ttemayo) <khoang65@gmail.com>
## SPDX-License-Identifier: GPL-2.0-or-later
## Userspace rules.mk
##
## NOTE: This is included in build AFTER keyboard specific rules 

SRC += ttemayo.c
SRC += vimdows.c

# ttemayo's Custom Features
ifeq ($(strip $(TTEMAYO_SYM_MACROS_ENABLE)), yes)
    OPT_DEFS += -DTTEMAYO_SYM_MACROS_ENABLE
endif

ifeq ($(strip $(VIMDOWS_ENABLE)), yes)
    OPT_DEFS += -DVIMDOWS_ENABLE
endif

#ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
#  SRC += tap_dance.c
#endif
