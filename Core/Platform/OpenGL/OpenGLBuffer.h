/*
 * OpenGLBuffer.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 11/04/2025
 */

#ifndef RIFT_OPENGLBUFFER_H
#define RIFT_OPENGLBUFFER_H

#include "Renderer/Buffer.h"

namespace Rift {
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer( float *data, uint32_t size );
        ~OpenGLVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

    private:
        uint32_t rendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer( uint32_t *data, uint32_t count );
        ~OpenGLIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        uint32_t GetCount() const override { return count; }

    private:
        uint32_t rendererID;
        uint32_t count = 0;
    };
} // namespace Rift

#endif
