/*
 * OpenGLBuffer.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 11/04/2025
 */

#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Rift {
    OpenGLVertexBuffer::OpenGLVertexBuffer( float *data, uint32_t size ) {
        glCreateBuffers( 1, &rendererID );
        glBindBuffer( GL_ARRAY_BUFFER, rendererID );
        glBufferData( GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW );
    }
    OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers( 1, &rendererID ); }

    void OpenGLVertexBuffer::Bind() const { glBindBuffer( GL_ARRAY_BUFFER, rendererID ); }
    void OpenGLVertexBuffer::Unbind() const { glBindBuffer( GL_ARRAY_BUFFER, 0 ); }

    OpenGLIndexBuffer::OpenGLIndexBuffer( uint32_t *data, uint32_t count ) : count( count ) {
        glCreateBuffers( 1, &rendererID );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, rendererID );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( uint32_t ), data, GL_STATIC_DRAW );
    }
    OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers( 1, &rendererID ); }

    void OpenGLIndexBuffer::Bind() const { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, rendererID ); }
    void OpenGLIndexBuffer::Unbind() const { glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); }
} // namespace Rift
