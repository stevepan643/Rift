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
#include "GLFW/glfw3.h"

namespace Rift {
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImGuiLayer::OnDetach() {
    }

    void ImGuiLayer::OnUpdate(float delta) {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float) glfwGetTime();
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