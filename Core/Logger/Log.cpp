/*
 * Log.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks-inl.h"

namespace Rift {

    Ref<spdlog::logger> Log::CoreLogger;
    Ref<spdlog::logger> Log::ClientLogger;

    void Log::Init() {
        spdlog::set_pattern( "%^[%H:%M:%S] [%n] [%l]: %v%$" );

        CoreLogger   = spdlog::stdout_color_mt( "CORE" );
        ClientLogger = spdlog::stdout_color_mt( "RIFT" );

        CoreLogger->set_level( spdlog::level::trace );
        ClientLogger->set_level( spdlog::level::trace );
    }

} // namespace Rift
