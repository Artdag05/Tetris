cmake_minimum_required(VERSION 3.23.1)

project(tetris)

set(SOURCES
    source/field.cpp
    source/game.cpp
    source/tetramino.cpp
    source/timer.cpp
    source/window.cpp
    main.cpp)

add_executable(tetris ${SOURCES})

target_include_directories(tetris
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include)