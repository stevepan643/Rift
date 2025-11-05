add_library(Core STATIC
        Core/Base.h
        Core/Assert.h
        Event/Event.h
        Window/Window.h
        Window/Window.cpp
        Window/WindowEvents.h
        Layer/Layer.cpp
        Layer/Layer.h
        Layer/LayerStack.cpp
        Layer/LayerStack.h
        Logger/Log.cpp
        Logger/Log.h
        ImGUI/ImGuiLayer.cpp
        ImGUI/ImGuiLayer.h
        App/Application.cpp
        App/Application.h
        App/EntryPoint.h
        Input/MouseEvents.h
        Input/KeyEvents.h
        Platform/Win/WinWindow.cpp
        Platform/Win/WinWindow.h
        Platform/OpenGL/ImGuiOpenGLRenderer.h
        Platform/OpenGL/ImGuiOpenGLRenderer.cpp
        Platform/OpenGL/ImGuiOpenGLLoader.h
        Platform/GLFW/ImGuiGLFWRenderer.cpp
        Platform/GLFW/ImGuiGLFWRenderer.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLContext.h
        Platform/OpenGL/OpenGLBuffer.h
        Platform/OpenGL/OpenGLBuffer.cpp
        Renderer/GraphicsContext.h
        Renderer/Shader.cpp
        Renderer/Shader.h
        Renderer/Buffer.h
        Renderer/Buffer.cpp
        Renderer/Renderer.cpp
        Renderer/Renderer.h
)

target_link_libraries(Core PUBLIC
        spdlog::spdlog
        glfw
        glad
        ImGui::imgui
        glm::glm
)

target_precompile_headers(Core PUBLIC pch.cpp pch.h)

include_directories(.)