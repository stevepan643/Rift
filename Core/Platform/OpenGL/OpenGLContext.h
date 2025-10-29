/*
 * OpenGLContext.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/29/2025
 */

#ifndef RIFT_OPENGLCONTEXT_H
#define RIFT_OPENGLCONTEXT_H
#include "GLFW/glfw3.h"
#include "Renderer/GraphicsContext.h"

namespace Rift {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext( GLFWwindow *windowHandle );

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow *window;
    };

} // namespace Rift

#endif // RIFT_OPENGLCONTEXT_H
