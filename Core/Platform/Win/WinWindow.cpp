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
#include "Logger/Log.h"
#include "Window/WindowEvents.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rift {
    static bool GLFWInitialized = false;

    WinWindow::WinWindow(const WindowProps &props) {
        Init(props);
    }

    WinWindow::~WinWindow() {
        Shutdown();
    }

    void WinWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(Window);
    }

    void WinWindow::SetVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        Data.VSync = enabled;
    }

    bool WinWindow::IsVSync() const {
        return Data.VSync;
    }

    void WinWindow::Init(const WindowProps &props) {
        Data.Width = props.Width;
        Data.Height = props.Height;
        Data.Title = props.Title;

        CORE_LOGGER_TRACE("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!GLFWInitialized) {
            int result = glfwInit();
            RF_CORE_ASSERT(result, "GLFW Initialization failed!");
            glfwSetErrorCallback([](int, const char* description) { SystemEvent->Publish(WindowErrorEvent(description)); });
            GLFWInitialized = true;
        }

        Window = glfwCreateWindow((int)props.Width, (int)props.Height, Data.Title.c_str(), nullptr, nullptr);
        RF_CORE_ASSERT(Window, "Failed to create GLFW window!");
        glfwMakeContextCurrent(Window);
        int result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RF_CORE_ASSERT(result, "Failed to initialize GLAD!");
        glfwSetWindowUserPointer(Window, &Data);
        SetVSync(true);

        glfwSetWindowSizeCallback(Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            SystemEvent->Publish(WindowResizeEvent(width, height));
        });

        glfwSetWindowCloseCallback(Window, [](GLFWwindow* window) {
            SystemEvent->Publish(WindowCloseEvent());
        });
    }

    void WinWindow::Shutdown() {
        glfwTerminate();
    }
} // Rift