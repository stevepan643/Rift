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
#include "Window/Window.h"

struct GLFWwindow;

namespace Rift {
    class WinWindow : public Window {
    public:
        WinWindow(const WindowProps& props);
        ~WinWindow() override;

        void OnUpdate() override;

        unsigned int GetWidth() const override { return Data.Width; }
        unsigned int GetHeight() const override { return Data.Height; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual void* GetNativeWindow() const { return Window; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();
    private:
        GLFWwindow* Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData Data;
    };
} // Rift

#endif //RIFT_WINWINDOW_H