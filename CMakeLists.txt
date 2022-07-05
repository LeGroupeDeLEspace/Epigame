cmake_minimum_required(VERSION 3.13.0)


project(jeudelespace)

add_executable(bonjourmonde)
target_compile_features(bonjourmonde PUBLIC cxx_std_17)
include_directories(bonjourmonde include)
add_subdirectory(src)

add_subdirectory(lib)

target_link_libraries(bonjourmonde graphRender glfw)

# move shaders
# configure_file(./lib/graphical/shaders/base.frag.spv ./shaders/frag.spv COPYONLY)
# configure_file(./lib/graphical/shaders/base.vert.spv ./shaders/vert.spv COPYONLY)
