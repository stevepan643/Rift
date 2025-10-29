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
#include "Input/MouseEvents.h"
#include "Window/WindowEvents.h"

class Sandbox : public Rift::Application {
};

Rift::Application* Rift::CreateApplication() { return new Sandbox(); }
