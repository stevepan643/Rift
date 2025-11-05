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

            layout(location = 0) in vec3 aPos;

            out vec3 v_Position;

            void main() {
                v_Position = aPos;
                gl_Position = vec4(aPos, 1.0);
            }
        )",
                                      R"(
            #version 410

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main() {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
        )" );

        glGenVertexArrays( 1, &vertexArray );
        glBindVertexArray( vertexArray );

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
        };

        vertexBuffer.reset( VertexBuffer::Create( vertices, sizeof( vertices ) ) );
        // vertexBuffer->Bind();

        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), nullptr );

        uint32_t indices[] = { 0, 1, 2 };
        indexBuffer.reset( IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint32_t ) ) );
        // indexBuffer->Bind();
    }

    Application::~Application() {}

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
