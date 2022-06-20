cmake_minimum_required(VERSION 3.13.0)

project(graphicalRender)

add_library(graphRender)
target_include_directories(graphRender PUBLIC include)
add_subdirectory(src)

find_package(Vulkan REQUIRED FATAL_ERROR)

target_include_directories(graphRender PUBLIC ${Vulkan_INCLUDE_DIRS})

target_link_libraries(graphRender PUBLIC glfw vulkan)
