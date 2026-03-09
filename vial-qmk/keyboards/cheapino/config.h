// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define WS2812_PIO_USE_PIO1
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB

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
