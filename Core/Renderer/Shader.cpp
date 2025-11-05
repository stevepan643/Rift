/*
 * Shader.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/29/2025
 */

#include "Shader.h"

#include "Platform/OpenGL/ImGuiOpenGLLoader.h"

namespace Rift {
    Shader::Shader( const std::string &vertexSrc, const std::string &fragmentSrc ) {
        GLint         success = 0;
        const GLchar *source;

        GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

        source = vertexSrc.c_str();
        glShaderSource( vertexShader, 1, &source, nullptr );

        glCompileShader( vertexShader );
        glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
        if ( success == GL_FALSE ) {
            GLint length = 0;
            glGetShaderiv( vertexShader, GL_INFO_LOG_LENGTH, &length );

            std::vector<GLchar> infoLog( length );
            glGetShaderInfoLog( vertexShader, length, &length, &infoLog[0] );

            glDeleteShader( vertexShader );

            CORE_LOGGER_ERROR( "{}", infoLog.data() );
            RF_CORE_ASSERT( false, "Vertex shader compile error!" );
            return;
        }

        GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

        source = fragmentSrc.c_str();
        glShaderSource( fragmentShader, 1, &source, nullptr );

        glCompileShader( fragmentShader );
        glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
        if ( success == GL_FALSE ) {
            GLint length = 0;
            glGetShaderiv( fragmentShader, GL_INFO_LOG_LENGTH, &length );

            std::vector<GLchar> infoLog( length );
            glGetShaderInfoLog( fragmentShader, length, &length, &infoLog[0] );

            glDeleteShader( fragmentShader );

            CORE_LOGGER_ERROR( "{}", infoLog.data() );
            RF_CORE_ASSERT( false, "Fragment shader compile error!" );
            return;
        }

        rendererID = glCreateProgram();

        glAttachShader( rendererID, vertexShader );
        glAttachShader( rendererID, fragmentShader );

        glLinkProgram( rendererID );

        GLint isLinked = 0;
        glGetProgramiv( rendererID, GL_LINK_STATUS, &isLinked );
        if ( isLinked == GL_FALSE ) {
            GLint length = 0;
            glGetProgramiv( rendererID, GL_INFO_LOG_LENGTH, &length );

            std::vector<GLchar> infoLog( length );
            glGetProgramInfoLog( rendererID, length, &length, &infoLog[0] );

            glDeleteProgram( rendererID );
            glDeleteShader( vertexShader );
            glDeleteShader( fragmentShader );

            CORE_LOGGER_ERROR( "{}", infoLog.data() );
            RF_CORE_ASSERT( false, "Program link error!" );
            return;
        }

        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );
    }

    Shader::~Shader() { glDeleteProgram( rendererID ); }

    void Shader::Bind() const { glUseProgram( rendererID ); }

    void Shader::Unbind() const { glUseProgram( 0 ); }
} // namespace Rift
