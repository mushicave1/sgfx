cmake_minimum_required(VERSION 3.1...3.25)

project(
    sgfx
    VERSION 0.1.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

add_subdirectory(test)