/*
 * Base.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_BASE_H
#define RIFT_BASE_H

#define BIT( x ) ( 1 << x )

namespace Rift {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope( Args &&...args ) {
        return std::make_unique<T>( std::forward<Args>( args )... );
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef( Args &&...args ) {
        return std::make_shared<T>( std::forward<Args>( args )... );
    }

} // namespace Rift

#endif // RIFT_BASE_H
