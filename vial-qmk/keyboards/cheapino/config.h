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

// A tap-hold key on a chordal_hold_layout 'L'/'R' position never resolves to
// its modifier/layer function on a timeout alone: 5 seconds is far longer
// than any typing pause, so in practice the only way it settles as a hold is
// a chordal-hold interrupt -- i.e. an opposite-hand key (or one of the two
// [D]/[K] same-hand exceptions in chordal_hold.c).  Anything else, including
// a deliberate solo hold with nothing else pressed, falls through to a plain
// tap.  Chordal hold's own interrupt-based decision is unaffected by this: it
// always resolves immediately, independent of how long the tapping term is.
// Used by musclememory/keymap.c's get_tapping_term(). Kept at keyboard level
// rather than duplicated, for whenever a second keymap can use it too.
//
// NOT applied to the vial keymap: quantum/vial.c defines its own strong,
// unconditional get_tapping_term() whenever VIAL_ENABLE=yes (it backs
// Vial-GUI-configurable per-tap-dance timing), which collides with any
// keymap-level definition at link time. Unlike the QMK_SETTINGS/
// get_chordal_hold() collision this isn't gated by a build flag, so it can't
// be sidestepped without patching vial-qmk itself. Until that's worth doing,
// the vial keymap keeps the plain flat TAPPING_TERM for these keys.
#define HOME_ROW_MOD_TERM 5000

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
