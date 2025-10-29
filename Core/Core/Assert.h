/*
 * Assert.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_ASSERT_H
#define RIFT_ASSERT_H

#include "Logger/Log.h"

#ifndef NDEBUG
#define RF_ENABLE_ASSERTS
#endif

#ifdef RF_ENABLE_ASSERTS
#ifdef _MSC_VER
#define RF_DEBUGBREAK() __debugbreak()
#else
#include <csignal>
// #define RF_DEBUGBREAK() raise( SIG_ERR )
#define RF_DEBUGBREAK() __debugbreak()
#endif
#define RF_CORE_ASSERT( x, ... )                                                                                       \
    {                                                                                                                  \
        if ( !( x ) ) {                                                                                                \
            CORE_LOGGER_CRITICAL( __VA_ARGS__ );                                                                       \
            RF_DEBUGBREAK();                                                                                           \
        }                                                                                                              \
    }
#else
#define RF_CORE_ASSERT( x, ... )
#endif

#endif // RIFT_ASSERT_H
