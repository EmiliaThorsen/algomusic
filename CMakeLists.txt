cmake_minimum_required(VERSION 3.10)

project(algomusic)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(program ./src/playBack/playBack.c ./src/main.c ./src/math/audioMath.c ./src/math/computer.c ./src/math/computerFunctions.c)

find_package(portaudio)

target_link_libraries(program portaudio)

set(CMAKE_C_FLAGS -lm)

target_compile_options(program PUBLIC -Wall -Wextra -g)
