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

void GLAPIENTRY GLDebugMessageCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                        const GLchar *message, const void *userParam ) {
    std::string sourceStr;
    switch ( source ) {
        case GL_DEBUG_SOURCE_API:
            sourceStr = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            sourceStr = "Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            sourceStr = "Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            sourceStr = "Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            sourceStr = "Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            sourceStr = "Other";
            break;
    }

    std::string typeStr;
    switch ( type ) {
        case GL_DEBUG_TYPE_ERROR:
            typeStr = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            typeStr = "Deprecated Behavior";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            typeStr = "Undefined Behavior";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            typeStr = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            typeStr = "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            typeStr = "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            typeStr = "Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            typeStr = "Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            typeStr = "Other";
            break;
    }

    std::string severityStr;
    switch ( severity ) {
        case GL_DEBUG_SEVERITY_HIGH:
            severityStr = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severityStr = "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severityStr = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severityStr = "NOTIFICATION";
            break;
    }

    // 根据严重程度输出不同日志级别
    if ( severity == GL_DEBUG_SEVERITY_HIGH ) {
        CORE_LOGGER_CRITICAL( "[OpenGL] [{}] [{}] [{}]: {}", sourceStr, typeStr, severityStr, message );
    } else if ( severity == GL_DEBUG_SEVERITY_MEDIUM ) {
        CORE_LOGGER_ERROR( "[OpenGL] [{}] [{}] [{}]: {}", sourceStr, typeStr, severityStr, message );
    } else if ( severity == GL_DEBUG_SEVERITY_LOW ) {
        CORE_LOGGER_WARN( "[OpenGL] [{}] [{}] [{}]: {}", sourceStr, typeStr, severityStr, message );
    } else {
        // CORE_LOGGER_TRACE("[OpenGL] [{}] [{}] [{}]: {}", sourceStr, typeStr, severityStr, message);
    }
}

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

        glEnable( GL_DEBUG_OUTPUT );
        glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
        glDebugMessageCallback( GLDebugMessageCallback, nullptr );
        glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE );
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers( window ); }
} // namespace Rift
