file(GLOB_RECURSE RIFTEDITOR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(RiftEditor ${RIFTEDITOR_SOURCES})

target_include_directories(RiftEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(RiftEditor PRIVATE RiftCore)
