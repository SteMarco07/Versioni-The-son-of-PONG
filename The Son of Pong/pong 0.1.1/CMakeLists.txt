cmake_minimum_required(VERSION 3.21)
project(pong)

set(CMAKE_CXX_STANDARD 14)

add_executable(pong main.cpp)

find_library(RAYLIBRARY raylib lib)

target_link_libraries(pong LINK_PUBLIC ${RAYLIBRARY} winmm)