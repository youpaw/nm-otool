cmake_minimum_required(VERSION 3.17)
project(otool C)

set(CMAKE_C_STANDARD 99)

add_executable(otool otool.c)
target_link_libraries(otool ft share)