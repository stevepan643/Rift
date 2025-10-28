/* 
 * Window.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_WINDOW_H
#define RIFT_WINDOW_H

namespace Rift {
    struct WindowProps {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "Rift Engine",
                    uint32_t width = 1600,
                    uint32_t height = 900)
             : Title(title), Width(width), Height(height) { }
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        // Window attributes
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
} // Rift

#endif //RIFT_WINDOW_H