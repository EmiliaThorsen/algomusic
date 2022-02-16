cmake_minimum_required(VERSION 3.10)

project(algomusic)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(program ./src/main.c ./src/audioMath.c)

find_package(portaudio)

target_link_libraries(program portaudio)

set(CMAKE_C_FLAGS -lm)
