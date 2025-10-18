file(GLOB_RECURSE RIFTCORE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(RiftCore STATIC ${RIFTCORE_SOURCES})

target_link_libraries(RiftCore PUBLIC spdlog::spdlog)

target_include_directories(RiftCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
