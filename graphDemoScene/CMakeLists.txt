cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

project(graphTestScene)

add_executable(out)

target_compile_features(out PUBLIC cxx_std_20)

include_directories(out include)

add_subdirectory(src)

target_link_libraries(out graphRender glfw)