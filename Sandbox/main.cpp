/*
 * main.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "Logger/Log.h"
#include "App/EntryPoint.h"
#include "Event/Event.h"
#include "Window/WindowEvents.h"

class Sandbox : public Rift::Application {
public:
    Sandbox() {
        Rift::SystemEvent->Subscribe<Rift::WindowCloseEvent>([](const Rift::WindowCloseEvent& e) {
            RIFT_LOGGER_INFO("Window Closed");
        });
    }
};

Rift::Application* Rift::CreateApplication() { return new Sandbox(); }
