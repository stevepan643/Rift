/*
 * OpenGLContext.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/29/2025
 */

#include "OpenGLContext.h"

#include "glad/glad.h"

namespace Rift {
    OpenGLContext::OpenGLContext( GLFWwindow *windowHandle ) : window( windowHandle ) {
        RF_CORE_ASSERT( windowHandle, "Window handle is null!" )
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent( window );
        int result = gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );
        RF_CORE_ASSERT( result, "Failed to initialize GLAD!" );

        CORE_LOGGER_TRACE( "OpenGL vendor: {}", reinterpret_cast<const char *>( glGetString( GL_VENDOR ) ) );
        CORE_LOGGER_TRACE( "OpenGL version: {}", reinterpret_cast<const char *>( glGetString( GL_VERSION ) ) );
        CORE_LOGGER_TRACE( "OpenGL renderer: {}", reinterpret_cast<const char *>( glGetString( GL_RENDERER ) ) );
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers( window ); }
} // namespace Rift
