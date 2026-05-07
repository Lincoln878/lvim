cmake_minimum_required(VERSION 4.1)
project(lvim)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

find_package(Curses REQUIRED)
add_executable(lvim
        main.cpp
        Editor.cpp
        Editor.h
)

target_include_directories(lvim PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(lvim PRIVATE ${CURSES_LIBRARIES})