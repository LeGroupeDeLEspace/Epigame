cmake_minimum_required(VERSION 3.13.0)

target_sources(bonjourmonde PRIVATE
    main.cpp
    TestWindow.cpp
    Logger.cpp
)

add_subdirectory(Utils)
add_subdirectory(Inputs)
