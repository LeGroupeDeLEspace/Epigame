cmake_minimum_required(VERSION 3.13.0)

target_sources(bonjourmonde PRIVATE
        GameScene.cpp
)

add_subdirectory(characterController)
add_subdirectory(components)
