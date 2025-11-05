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
#include "App/Application.h"
#include "GLFW/glfw3.h"
#include "Logger/Log.h"
#include "Platform/GLFW/ImGuiGLFWRenderer.h"
#include "Platform/OpenGL/ImGuiOpenGLLoader.h"
#include "Window/WindowEvents.h"
#include "imgui_impl_opengl3.h"

namespace Rift {

    ImGuiLayer::ImGuiLayer() : Layer( "ImGuiLayer" ) {}

    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
            style.WindowRounding              = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application &app    = Application::Get();
        GLFWwindow  *window = static_cast<GLFWwindow *>( app.GetWindow().GetNativeWindow() );

        ImGui_ImplGlfw_InitForOpenGL( window, true );
        ImGui_ImplOpenGL3_Init( "#version 330 core" );
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate( float delta ) {}

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO     &io  = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize   = ImVec2( static_cast<float>( app.GetWindow().GetWidth() ),
                                   static_cast<float>( app.GetWindow().GetHeight() ) );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ) {
            GLFWwindow *backendCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent( backendCurrentContext );
        }
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool show = true;
        ImGui::ShowDemoWindow( &show );
    }
} // namespace Rift
