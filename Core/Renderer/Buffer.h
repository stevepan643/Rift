/*
 * Buffer.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/29/2025
 */

#ifndef RIFT_BUFFER_H
#define RIFT_BUFFER_H
#include <cstdint>

namespace Rift {

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer *Create( float *data, uint32_t size );
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer *Create( uint32_t *data, uint32_t count );
    };
} // namespace Rift

#endif // RIFT_BUFFER_H
