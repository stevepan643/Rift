/* 
 * EntryPoint.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_ENTRYPOINT_H
#define RIFT_ENTRYPOINT_H

#include "App/Application.h"

extern Rift::Application* Rift::CreateApplication();

int main(int argc, char** argv) {
    Rift::Log::Init();

    auto app = Rift::CreateApplication();

    app->Run();

    delete app;
}

#endif //RIFT_ENTRYPOINT_H