/*
 * WinWindow.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_WINWINDOW_H
#define RIFT_WINWINDOW_H

#include "Event/Event.h"
#include "Renderer/GraphicsContext.h"
#include "Window/Window.h"

struct GLFWwindow;

namespace Rift {
    class WinWindow : public Window {
    public:
        WinWindow( const WindowProps &props );
        ~WinWindow() override;

        void OnUpdate() override;

        unsigned int GetWidth() const override { return data.width; }
        unsigned int GetHeight() const override { return data.height; }

        void SetVSync( bool enabled ) override;
        bool IsVSync() const override;

        virtual void *GetNativeWindow() const { return window; }

    private:
        virtual void Init( const WindowProps &props );
        virtual void Shutdown();

    private:
        GLFWwindow      *window;
        GraphicsContext *context;

        struct WindowData {
            std::string  title;
            unsigned int width, height;
            bool         isVSync;

            EventCallbackFn eventCallback;
        };

        WindowData data;
    };
} // namespace Rift

#endif // RIFT_WINWINDOW_H
