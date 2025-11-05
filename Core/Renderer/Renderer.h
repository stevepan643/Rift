/*
 * Renderer.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 11/05/2025
 */

#ifndef RIFT_RENDERER_H
#define RIFT_RENDERER_H

namespace Rift {
    enum class RendererAPI {
        None   = 0,
        OpenGL = 1,
    };

    class Renderer {
    public:
        static RendererAPI GetAPI() { return rendererAPI; }

    private:
        static RendererAPI rendererAPI;
    };
} // namespace Rift

#endif // RIFT_RENDERER_H
