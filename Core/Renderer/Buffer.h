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

#include "Platform/OpenGL/ImGuiOpenGLLoader.h"
// #include "glad/glad.h"

#include <cstdint>

namespace Rift {

    enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

    static GLenum ShaderDataTypeToOpenGLBaseType( ShaderDataType type ) {
        switch ( type ) {
            case ShaderDataType::Float:
                return GL_FLOAT;
            case ShaderDataType::Float2:
                return GL_FLOAT;
            case ShaderDataType::Float3:
                return GL_FLOAT;
            case ShaderDataType::Float4:
                return GL_FLOAT;
            case ShaderDataType::Mat3:
                return GL_FLOAT;
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
                return GL_INT;
            case ShaderDataType::Int2:
                return GL_INT;
            case ShaderDataType::Int3:
                return GL_INT;
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
            default:
                return GL_NONE;
        }
    }

    static uint32_t BufferDataTypeSize( ShaderDataType type ) {
        switch ( type ) {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
            default:
                return 0;
        }
    }

    struct BufferElements {
        std::string    name;
        ShaderDataType type;
        uint32_t       offset;
        uint32_t       size;
        bool           normalized;

        BufferElements() = default;

        BufferElements( ShaderDataType type, const std::string &name, bool normalize = false ) :
            name( name ), type( type ), offset( 0 ), size( BufferDataTypeSize( type ) ), normalized( normalized ) {}

        uint32_t GetComponentCount() const {
            switch ( type ) {
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 3 * 3;
                case ShaderDataType::Mat4:
                    return 4 * 4;
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
                default:
                    return 0;
            }
        }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;

        BufferLayout( const std::initializer_list<BufferElements> &elements ) : elements( elements ) {
            CalculateOffsetAndStride();
        }

        const std::vector<BufferElements> &GetElements() const { return elements; }
        uint32_t                           GetStride() const { return stride; }

        std::vector<BufferElements>::iterator begin() { return elements.begin(); }
        std::vector<BufferElements>::iterator end() { return elements.end(); }
        std::vector<BufferElements>::const_iterator         begin() const { return elements.begin(); }
        std::vector<BufferElements>::const_iterator         end() const { return elements.end(); }

    private:
        void CalculateOffsetAndStride() {
            uint32_t offset = 0;
            stride          = 0;
            for ( BufferElements &element : elements ) {
                element.offset = offset;
                offset += element.size;
                stride += element.size;
            }
        }
        std::vector<BufferElements> elements;
        uint32_t                    stride = 0;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout &GetLayout() const                       = 0;
        virtual void                SetLayout( const BufferLayout &layout ) = 0;

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
