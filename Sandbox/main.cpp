/*
 * main.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "App/EntryPoint.h"
#include "Logger/Log.h"
#include "imgui.h"

class SandboxLayer : public Rift::Layer {
public:
    void OnAttach() override { RIFT_LOGGER_INFO( "Layer on attaching!" ); }

    void OnImGuiRender() override {
        ImGui::Begin( "Layers" );
        ImGui::Text( "Hello World!" );
        ImGui::End();
    }
};

class Sandbox : public Rift::Application {
public:
    Sandbox() { PushLayer( new SandboxLayer() ); }
};

Rift::Application *Rift::CreateApplication() { return new Sandbox(); }
