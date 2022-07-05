cmake_minimum_required(VERSION 3.13.0)

project(systemUtils)

add_library(systemUtils)
target_compile_features(systemUtils PUBLIC cxx_std_17)

target_include_directories(systemUtils PUBLIC include)
add_subdirectory(src)
