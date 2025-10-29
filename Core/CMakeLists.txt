add_library(Core STATIC
        Logger/Log.cpp
        Logger/Log.h
        Core/Base.h
        Event/Event.h
        Window/Window.h
        Window/Window.cpp
        Platform/Win/WinWindow.cpp
        Platform/Win/WinWindow.h
        Platform/OpenGL/ImGuiOpenGLRenderer.h
        Window/WindowEvents.h
        Core/Assert.h
        Layer/Layer.cpp
        Layer/Layer.h
        Layer/LayerStack.cpp
        Layer/LayerStack.h
        ImGUI/ImGuiLayer.cpp
        ImGUI/ImGuiLayer.h
        App/Application.cpp
        App/Application.h
        App/EntryPoint.h
        Platform/OpenGL/ImGuiOpenGLRenderer.cpp
        Platform/OpenGL/ImGuiOpenGLLoader.h
        Platform/GLFW/ImGuiGLFWRenderer.cpp
        Platform/GLFW/ImGuiGLFWRenderer.h
        Input/MouseEvents.h
        Input/KeyEvents.h
        Renderer/GraphicsContext.h
        Platform/OpenGL/OpenGLContext.cpp
        Platform/OpenGL/OpenGLContext.h
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