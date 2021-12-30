cmake_minimum_required(VERSION 3.10)

project(algomusic)

add_executable(program ./src/main.c)

find_package(portaudio)

target_link_libraries(program portaudio)

set(CMAKE_C_FLAGS -lm)
