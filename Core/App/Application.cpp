/*
 * Application.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "Application.h"

#include "Event/Event.h"
#include "Window/WindowEvents.h"

#include <ranges>

namespace Rift {
    Application *Application::instance = nullptr;

    Application::Application() {
        RF_CORE_ASSERT( !instance, "Application already exists" );
        instance = this;

        window     = Window::Create();
        imGuiLayer = new ImGuiLayer();
        PushOverlay( imGuiLayer );

        SystemEvent->Subscribe<WindowCloseEvent>( [this]( const WindowCloseEvent & ) { Close(); } );

        shader = CreateScope<Shader>( R"(
            #version 410

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )",
                                      R"(
            #version 410

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main() {
                color = v_Color;
            }
        )" );

        glGenVertexArrays( 1, &vertexArray );
        glBindVertexArray( vertexArray );

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, 0.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,  1.0f,
        };

        vertexBuffer.reset( VertexBuffer::Create( vertices, sizeof( vertices ) ) );

        {
            BufferLayout layout = { { ShaderDataType::Float3, "a_Position" }, { ShaderDataType::Float4, "a_Color" } };

            vertexBuffer->SetLayout( layout );
        }

        uint32_t index = 0;
        for ( const auto &element : vertexBuffer->GetLayout() ) {
            glEnableVertexAttribArray( index );
            glVertexAttribPointer( index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType( element.type ),
                                   element.normalized ? GL_TRUE : GL_FALSE, vertexBuffer->GetLayout().GetStride(),
                                   reinterpret_cast<const void*>(static_cast<uintptr_t>(element.offset)) );
            index++;
        }

        uint32_t indices[] = { 0, 1, 2 };
        indexBuffer.reset( IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint32_t ) ) );
    }

    Application::~Application() = default;

    void Application::PushLayer( Layer *layer ) {
        layerStack.PushLayer( layer );
        layer->OnAttach();
    }

    void Application::PushOverlay( Layer *layer ) {
        layerStack.PushOverlay( layer );
        layer->OnAttach();
    }

    void Application::Close() { running = false; }

    void Application::Run() {
        while ( running ) {
            glClear( GL_COLOR_BUFFER_BIT );

            shader->Bind();
            glBindVertexArray( vertexArray );
            glDrawElements( GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr );

            for ( Layer *layer : layerStack )
                layer->OnUpdate( 0.0f );

            imGuiLayer->Begin();
            for ( Layer *layer : layerStack )
                layer->OnImGuiRender();
            imGuiLayer->End();

            window->OnUpdate();
        }
    }
} // namespace Rift
