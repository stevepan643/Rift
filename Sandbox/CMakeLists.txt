file(GLOB_RECURSE SANDBOX_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(Sandbox ${SANDBOX_SOURCES})

target_include_directories(Sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Sandbox PRIVATE RiftCore)
