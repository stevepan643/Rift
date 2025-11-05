/*
 * Buffer.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 11/05/2025
 */

#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Rift {
    VertexBuffer *VertexBuffer::Create( float *data, uint32_t size ) {
        switch ( Renderer::GetAPI() ) {
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer( data, size );
            case RendererAPI::None:
                return nullptr;
        }
        RF_CORE_ASSERT( false, "Unknown RendererAPI" );
        return nullptr;
    }

    IndexBuffer *IndexBuffer::Create( uint32_t *data, uint32_t size ) {
        switch ( Renderer::GetAPI() ) {
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer( data, size );
            case RendererAPI::None:
                return nullptr;
        }
        RF_CORE_ASSERT( false, "Unknown RendererAPI" );
        return nullptr;
    }
} // namespace Rift
