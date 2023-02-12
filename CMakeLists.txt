cmake_minimum_required(VERSION 3.24)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.0.22
)
FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.20.1
)
FetchContent_MakeAvailable(SDL2 SDL2_ttf)

add_executable(Tetris src/main.cpp)

target_link_libraries(Tetris
        PUBLIC SDL2
        PUBLIC SDL2_ttf)
