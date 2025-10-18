cmake_minimum_required(VERSION 4.0)
project(Rift LANGUAGES CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(ThirdParty/spdlog)

add_subdirectory(RiftCore)
add_subdirectory(Sandbox)
add_subdirectory(RiftEditor)
