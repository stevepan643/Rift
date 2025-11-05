/*
 * WinWindow.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "WinWindow.h"

#include "Core/Assert.h"
#include "GLFW/glfw3.h"
#include "Input/KeyEvents.h"
#include "Input/MouseEvents.h"
#include "Logger/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Window/WindowEvents.h"

namespace Rift {
    static bool GLFWInitialized = false;

    WinWindow::WinWindow( const WindowProps &props ) { Init( props ); }

    WinWindow::~WinWindow() { Shutdown(); }

    void WinWindow::OnUpdate() {
        glfwPollEvents();
        context->SwapBuffers();
    }

    void WinWindow::SetVSync( bool enabled ) {
        if ( enabled )
            glfwSwapInterval( 1 );
        else
            glfwSwapInterval( 0 );
        data.isVSync = enabled;
    }

    bool WinWindow::IsVSync() const { return data.isVSync; }

    void WinWindow::Init( const WindowProps &props ) {
        data.width  = props.Width;
        data.height = props.Height;
        data.title  = props.Title;

        CORE_LOGGER_TRACE( "Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height );

        if ( !GLFWInitialized ) {
            int result = glfwInit();
            RF_CORE_ASSERT( result, "GLFW Initialization failed!" );
            glfwSetErrorCallback(
                    []( int, const char *description ) { SystemEvent->Publish( WindowErrorEvent( description ) ); } );
            GLFWInitialized = true;
        }

        window = glfwCreateWindow( ( int ) props.Width, ( int ) props.Height, data.title.c_str(), nullptr, nullptr );
        RF_CORE_ASSERT( window, "Failed to create GLFW window!" );

        context = new OpenGLContext( window );
        context->Init();

        glfwSetWindowUserPointer( window, &data );
        SetVSync( true );

        glfwSetWindowSizeCallback( window, []( GLFWwindow *window, int width, int height ) {
            WindowData &data = *( WindowData * ) glfwGetWindowUserPointer( window );
            data.width       = width;
            data.height      = height;

            SystemEvent->Publish( WindowResizeEvent( width, height ) );
        } );

        glfwSetWindowCloseCallback( window, []( GLFWwindow * ) { SystemEvent->Publish( WindowCloseEvent() ); } );

        glfwSetKeyCallback( window, []( GLFWwindow *, const int key, int, int action, int ) {
            switch ( action ) {
                case GLFW_PRESS: {
                    SystemEvent->Publish( KeyPressedEvent( key ) );
                    break;
                }
                case GLFW_RELEASE: {
                    SystemEvent->Publish( KeyReleasedEvent( key ) );
                    break;
                }
                case GLFW_REPEAT: {
                    SystemEvent->Publish( KeyPressedEvent( key, true ) );
                    break;
                }
                default:;
            }
        } );

        glfwSetCharCallback( window, []( GLFWwindow *, unsigned int codepoint ) {
            SystemEvent->Publish( KeyTypedEvent( codepoint ) );
        } );

        glfwSetMouseButtonCallback( window, []( GLFWwindow *, int button, int action, int mods ) {
            switch ( action ) {
                case GLFW_PRESS: {
                    SystemEvent->Publish( MouseButtonPressedEvent( button ) );
                    break;
                }
                case GLFW_RELEASE: {
                    SystemEvent->Publish( MouseButtonReleasedEvent( button ) );
                    break;
                }
                default:;
            }
        } );

        glfwSetScrollCallback( window, []( GLFWwindow *, double offsetX, double offsetY ) {
            SystemEvent->Publish( MouseScrolledEvent( static_cast<float>( offsetX ), static_cast<float>( offsetY ) ) );
        } );

        glfwSetCursorPosCallback( window, []( GLFWwindow *, double posX, double posY ) {
            SystemEvent->Publish( MouseMovedEvent( static_cast<float>( posX ), static_cast<float>( posY ) ) );
        } );
    }

    void WinWindow::Shutdown() { glfwTerminate(); }
} // namespace Rift
