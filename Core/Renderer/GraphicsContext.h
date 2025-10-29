/*
 * GraphicsContext.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/29/2025
 */

#ifndef RIFT_GRAPHICSCONTEXT_H
#define RIFT_GRAPHICSCONTEXT_H

namespace Rift {
    class GraphicsContext {
    public:
        virtual void Init()        = 0;
        virtual void SwapBuffers() = 0;
    };
} // namespace Rift

#endif // RIFT_GRAPHICSCONTEXT_H
