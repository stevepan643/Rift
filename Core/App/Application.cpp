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

#include "Core/Assert.h"
#include "Event/Event.h"
#include "Window/WindowEvents.h"
#include "glad/glad.h"

namespace Rift {
    Application *Application::instance = nullptr;

    Application::Application() {
        RF_CORE_ASSERT( !instance, "Application already exists" );
        instance = this;

        window     = Window::Create();
        imGuiLayer = new ImGuiLayer();
        PushOverlay( imGuiLayer );

        SystemEvent->Subscribe<WindowCloseEvent>( [this]( const WindowCloseEvent & ) { Close(); } );
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
