cmake_minimum_required(VERSION 3.13.0)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

project(jeudelespace)

add_executable(bonjourmonde)

target_compile_features(bonjourmonde PUBLIC cxx_std_20)

include_directories(bonjourmonde include)

add_subdirectory(src)

add_subdirectory(lib)

target_link_libraries(bonjourmonde graphRender glfw EnTT)

add_subdirectory(graphDemoScene)

# move shaders
 configure_file(${CMAKE_CURRENT_BINARY_DIR}/lib/graphical/shaders/base.frag.spv ${CMAKE_CURRENT_BINARY_DIR}/shaders/base.frag.spv COPYONLY)
 configure_file(${CMAKE_CURRENT_BINARY_DIR}/lib/graphical/shaders/base.vert.spv ${CMAKE_CURRENT_BINARY_DIR}/shaders/base.vert.spv COPYONLY)
