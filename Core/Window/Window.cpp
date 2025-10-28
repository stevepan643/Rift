/* 
 * Window.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "Window.h"

#include "Platform/Win/WinWindow.h"

namespace Rift {
    Scope<Window> Window::Create(const WindowProps& props) {
        return CreateScope<WinWindow>(props);
    }
} // Rift