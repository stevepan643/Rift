cmake_minimum_required(VERSION 3.5.0)
project(Rift VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(ThirdParty/spdlog)
add_subdirectory(ThirdParty/GLFW)
add_subdirectory(ThirdParty/GLAD)
add_subdirectory(ThirdParty/imgui)
add_subdirectory(ThirdParty/GLM)

add_subdirectory(Core)
add_subdirectory(Sandbox)
