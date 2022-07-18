cmake_minimum_required(VERSION 3.13.0)

target_sources(bonjourmonde PRIVATE
    main.cpp
    TestWindow.cpp
    Logger.cpp
)

add_subdirectory(generation)
add_subdirectory(utils)
add_subdirectory(inputs)
add_subdirectory(scene)
add_subdirectory(gameplay)
