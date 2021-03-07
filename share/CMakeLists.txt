cmake_minimum_required(VERSION 3.17)
project(share C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

ADD_LIBRARY(share STATIC share.c)

target_link_libraries(share ft)
target_include_directories(share PUBLIC .)