/*
 * Log.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_LOG_H
#define RIFT_LOG_H

#include "Core/Base.h"
#include "spdlog/spdlog.h"

namespace Rift {

    class Log {
    public:
        static void Init();

        static Ref<spdlog::logger> &GetCoreLogger() { return CoreLogger; }
        static Ref<spdlog::logger> &GetClientLogger() { return ClientLogger; }

    private:
        static Ref<spdlog::logger> CoreLogger;
        static Ref<spdlog::logger> ClientLogger;
    };

} // namespace Rift

// Core Logger Macros
#define CORE_LOGGER_TRACE( ... ) ::Rift::Log::GetCoreLogger()->trace( __VA_ARGS__ )
#define CORE_LOGGER_DEBUG( ... ) ::Rift::Log::GetCoreLogger()->debug( __VA_ARGS__ )
#define CORE_LOGGER_INFO( ... ) ::Rift::Log::GetCoreLogger()->info( __VA_ARGS__ )
#define CORE_LOGGER_WARN( ... ) ::Rift::Log::GetCoreLogger()->warn( __VA_ARGS__ )
#define CORE_LOGGER_ERROR( ... ) ::Rift::Log::GetCoreLogger()->error( __VA_ARGS__ )
#define CORE_LOGGER_CRITICAL( ... ) ::Rift::Log::GetCoreLogger()->critical( __VA_ARGS__ )

// Client Logger Macros
#define RIFT_LOGGER_TRACE( ... ) ::Rift::Log::GetClientLogger()->trace( __VA_ARGS__ )
#define RIFT_LOGGER_DEBUG( ... ) ::Rift::Log::GetClientLogger()->debug( __VA_ARGS__ )
#define RIFT_LOGGER_INFO( ... ) ::Rift::Log::GetClientLogger()->info( __VA_ARGS__ )
#define RIFT_LOGGER_WARN( ... ) ::Rift::Log::GetClientLogger()->warn( __VA_ARGS__ )
#define RIFT_LOGGER_ERROR( ... ) ::Rift::Log::GetClientLogger()->error( __VA_ARGS__ )
#define RIFT_LOGGER_CRITICAL( ... ) ::Rift::Log::GetClientLogger()->critical( __VA_ARGS__ )

#endif // RIFT_LOG_H
