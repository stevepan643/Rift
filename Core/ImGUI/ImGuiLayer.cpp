/* 
 * ImGuiLayer.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "ImGuiLayer.h"
#include "imgui_impl_opengl3.h"
#include "App/Application.h"
#include "Event/Event.h"
#include "GLFW/glfw3.h"
#include "Input/KeyEvents.h"
#include "Input/MouseEvents.h"
#include "Logger/Log.h"
#include "Platform/OpenGL/ImGuiOpenGLLoader.h"
#include "Window/WindowEvents.h"

namespace Rift {
    static ImGuiKey KeyCodeToImGuiKey(KeyCode key) {
        switch (key) {
            case Tab: return ImGuiKey_Tab;
            case Left: return ImGuiKey_LeftArrow;
            case Right: return ImGuiKey_RightArrow;
            case Up: return ImGuiKey_UpArrow;
            case Down: return ImGuiKey_DownArrow;
            case PageUp: return ImGuiKey_PageUp;
            case PageDown: return ImGuiKey_PageDown;
            case Home: return ImGuiKey_Home;
            case End: return ImGuiKey_End;
            case Insert: return ImGuiKey_Insert;
            case Delete: return ImGuiKey_Delete;
            case Backspace: return ImGuiKey_Backspace;
            case Space: return ImGuiKey_Space;
            case Enter: return ImGuiKey_Enter;
            case Escape: return ImGuiKey_Escape;

            // Modifiers
            case LeftControl: return ImGuiKey_LeftCtrl;
            case RightControl: return ImGuiKey_RightCtrl;
            case LeftShift: return ImGuiKey_LeftShift;
            case RightShift: return ImGuiKey_RightShift;
            case LeftAlt: return ImGuiKey_LeftAlt;
            case RightAlt: return ImGuiKey_RightAlt;
            case LeftSuper: return ImGuiKey_LeftSuper;
            case RightSuper: return ImGuiKey_RightSuper;

            // Letters
            case A: return ImGuiKey_A;
            case B: return ImGuiKey_B;
            case C: return ImGuiKey_C;
            case D: return ImGuiKey_D;
            case E: return ImGuiKey_E;
            case F: return ImGuiKey_F;
            case G: return ImGuiKey_G;
            case H: return ImGuiKey_H;
            case I: return ImGuiKey_I;
            case J: return ImGuiKey_J;
            case K: return ImGuiKey_K;
            case L: return ImGuiKey_L;
            case M: return ImGuiKey_M;
            case N: return ImGuiKey_N;
            case O: return ImGuiKey_O;
            case P: return ImGuiKey_P;
            case Q: return ImGuiKey_Q;
            case R: return ImGuiKey_R;
            case S: return ImGuiKey_S;
            case T: return ImGuiKey_T;
            case U: return ImGuiKey_U;
            case V: return ImGuiKey_V;
            case W: return ImGuiKey_W;
            case X: return ImGuiKey_X;
            case Y: return ImGuiKey_Y;
            case Z: return ImGuiKey_Z;

            case F1: return ImGuiKey_F1;
            case F2: return ImGuiKey_F2;
            case F3: return ImGuiKey_F3;
            case F4: return ImGuiKey_F4;
            case F5: return ImGuiKey_F5;
            case F6: return ImGuiKey_F6;
            case F7: return ImGuiKey_F7;
            case F8: return ImGuiKey_F8;
            case F9: return ImGuiKey_F9;
            case F10: return ImGuiKey_F10;
            case F11: return ImGuiKey_F11;
            case F12: return ImGuiKey_F12;

            default:
                return ImGuiKey_None;
        }
    }

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 460");

        SystemEvent->Subscribe<MouseButtonPressedEvent>([] (const MouseButtonPressedEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDown[e.GetMouseButton()] = true;
        });

        SystemEvent->Subscribe<MouseButtonReleasedEvent>([] (const MouseButtonReleasedEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDown[e.GetMouseButton()] = false;
        });

        SystemEvent->Subscribe<MouseMovedEvent>([] (const MouseMovedEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = ImVec2(e.GetX(), e.GetY());
        });

        SystemEvent->Subscribe<MouseScrolledEvent>([] (const MouseScrolledEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseWheel = e.GetOffsetY();
            io.MouseWheelH = e.GetOffsetX();
        });

        SystemEvent->Subscribe<WindowResizeEvent>([](const WindowResizeEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            Application& app = Application::Get();
            io.DisplaySize = ImVec2(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));

            glViewport(0, 0, e.GetWidth(), e.GetHeight());
        });

        SystemEvent->Subscribe<KeyPressedEvent>([](const KeyPressedEvent& e) {
            CORE_LOGGER_DEBUG("KeyCode: {}", e.GetKeyCode());
            ImGuiIO& io = ImGui::GetIO();
            ImGuiKey imguiKey = KeyCodeToImGuiKey(e.GetKeyCode());
            io.AddKeyEvent(imguiKey, true);

            io.AddKeyEvent(ImGuiMod_Ctrl, io.KeysDown[KeyCodeToImGuiKey(LeftControl)] || io.KeysDown[KeyCodeToImGuiKey(RightControl)]);
            io.AddKeyEvent(ImGuiMod_Shift, io.KeysDown[KeyCodeToImGuiKey(LeftShift)] || io.KeysDown[KeyCodeToImGuiKey(RightShift)]);
            io.AddKeyEvent(ImGuiMod_Alt, io.KeysDown[KeyCodeToImGuiKey(LeftAlt)] || io.KeysDown[KeyCodeToImGuiKey(RightAlt)]);
            io.AddKeyEvent(ImGuiMod_Super, io.KeysDown[KeyCodeToImGuiKey(LeftSuper)] || io.KeysDown[KeyCodeToImGuiKey(RightSuper)]);
        });

        SystemEvent->Subscribe<KeyReleasedEvent>([](const KeyReleasedEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            ImGuiKey imguiKey = KeyCodeToImGuiKey(e.GetKeyCode());
            io.AddKeyEvent(imguiKey, false);
        });

        SystemEvent->Subscribe<KeyTypedEvent>([](const KeyTypedEvent& e) {
            ImGuiIO& io = ImGui::GetIO();
            if (e.GetKeyCode() > 0 && e.GetKeyCode() < 0x10000)
                io.AddInputCharacter(e.GetKeyCode());
        });
    }

    void ImGuiLayer::OnDetach() {
    }

    void ImGuiLayer::OnUpdate(float delta) {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

        auto time = static_cast<float>(glfwGetTime());
        io.DeltaTime = time > 0 ? (time - this->time) : (1.0f / 60.0f);
        this->time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // Rift