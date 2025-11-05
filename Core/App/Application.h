/*
 * Application.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_APPLICATION_H
#define RIFT_APPLICATION_H

#include "ImGUI/ImGuiLayer.h"
#include "Layer/Layer.h"
#include "Layer/LayerStack.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Window/Window.h"

namespace Rift {
    class Application {
    public:
        Application();
        virtual ~Application();

        void PushLayer( Layer *layer );
        void PushOverlay( Layer *layer );

        void Run();

        void Close();

        Window             &GetWindow() const { return *window; }
        ImGuiLayer         *GetImGuiLayer() const { return imGuiLayer; }
        static Application &Get() { return *instance; }

    private:
        bool          running = true;
        Scope<Window> window;
        LayerStack    layerStack;
        ImGuiLayer   *imGuiLayer;

        Scope<Shader>       shader;
        GLuint              vertexArray;
        Scope<VertexBuffer> vertexBuffer;
        Scope<IndexBuffer>  indexBuffer;

        float lastFrameTime = 0.0f;

        static Application *instance;
    };

    Application *CreateApplication();
} // namespace Rift

#endif // RIFT_APPLICATION_H
