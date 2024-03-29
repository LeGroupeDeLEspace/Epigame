cmake_minimum_required(VERSION 3.13.0)

project(graphicalRender)

add_definitions(-D_USE_MATH_DEFINES)

add_library(graphRender)
target_compile_features(graphRender PUBLIC cxx_std_17)

target_include_directories(graphRender PUBLIC include)
add_subdirectory(src)

find_package(Vulkan REQUIRED FATAL_ERROR)

target_include_directories(graphRender PUBLIC ${Vulkan_INCLUDE_DIRS})

target_link_libraries(graphRender PUBLIC systemUtils glfw glm ${Vulkan_LIBRARIES})


# compile shaders

find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(MAKE_DIRECTORY ${SHADER_SOURCE_DIR})
file(MAKE_DIRECTORY ${SHADER_BINARY_DIR})

file(TOUCH "${SHADER_BINARY_DIR}/base.frag.spv" "${SHADER_BINARY_DIR}/base.vert.spv")

execute_process(COMMAND ${glslc_executable} "${SHADER_SOURCE_DIR}/base.frag" -o "${SHADER_BINARY_DIR}/base.frag.spv")
execute_process(COMMAND ${glslc_executable} "${SHADER_SOURCE_DIR}/base.vert" -o "${SHADER_BINARY_DIR}/base.vert.spv")

# file(GLOB SHADERS
#   ${SHADER_SOURCE_DIR}/*.vert
#   ${SHADER_SOURCE_DIR}/*.frag
# )

# add_custom_command(
#     COMMAND
#         ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
#     OUTPUT ${SHADER_BINARY_DIR}
#     COMMENT "Creating ${SHADER_BINARY_DIR}"
# )

# foreach(source IN LISTS SHADERS)
#   get_filename_component(FILENAME ${source} NAME)
#   add_custom_command(
#     COMMAND
#       ${glslc_executable}
#       -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
#       ${source}
#     OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
#     DEPENDS ${source} ${SHADER_BINARY_DIR}
#     COMMENT "Compiling ${FILENAME}"
#   )
#   list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
# endforeach()

# add_custom_target(shaders ALL DEPENDS ${SPV_SHADERS})

# includes shaders directory to lib
# target_include_directories(graphRender PUBLIC ${SHADER_BINARY_DIR})