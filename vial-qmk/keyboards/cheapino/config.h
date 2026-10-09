// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define WS2812_PIO_USE_PIO1
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB

// Home row mods resolve by the opposite-hands rule: a tap-hold key settles as
// TAPPED when the next key is on the same hand.  Handedness map and the
// same-hand exceptions are in chordal_hold.c.
#define CHORDAL_HOLD

// Baseline tapping term.  Set here rather than in keyboard.json because the
// schema key name for TAPPING_TERM has moved between QMK versions, and
// get_tapping_term() in the keymap uses this value as its default branch.
#define TAPPING_TERM 200

// Force these values regardless of what the JSON or other files say
#ifdef MOUSEKEY_ENABLE
    #undef MOUSEKEY_INTERVAL
    #define MOUSEKEY_INTERVAL 16

    #undef MOUSEKEY_INITIAL_SPEED
    #define MOUSEKEY_INITIAL_SPEED 2

    #undef MOUSEKEY_MOVE_DELTA
    #define MOUSEKEY_MOVE_DELTA 1  // Set to 1 for absolute precision testing

    #undef MOUSEKEY_MAX_SPEED
    #define MOUSEKEY_MAX_SPEED 14

    #undef MOUSEKEY_TIME_TO_MAX
    #define MOUSEKEY_TIME_TO_MAX 100
#endif
