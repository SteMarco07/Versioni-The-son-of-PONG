cmake_minimum_required(VERSION 3.21)
project(Pong)

set(CMAKE_CXX_STANDARD 14)

add_executable(Pong main.cpp)

find_library(RAYLIBRARY raylib lib)

target_link_libraries(Pong LINK_PUBLIC ${RAYLIBRARY} winmm)

set(CMAKE_EXE_LINKER_FLAGS "-static")