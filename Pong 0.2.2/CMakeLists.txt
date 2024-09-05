cmake_minimum_required(VERSION 3.21)
project(Pong_S_S)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pong_S_S main.cpp)

find_library(RAYLIBRARY raylib lib)

target_link_libraries(Pong_S_S LINK_PUBLIC ${RAYLIBRARY} winmm)