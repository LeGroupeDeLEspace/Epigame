cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

project(jeudelespace)

add_executable(bonjourmonde src/Inputs/InputAction.cpp)
include_directories(bonjourmonde include)
add_subdirectory(src)

add_subdirectory(lib)

target_link_libraries(bonjourmonde graphRender glfw)