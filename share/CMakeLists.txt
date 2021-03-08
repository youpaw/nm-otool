cmake_minimum_required(VERSION 3.17)
project(share C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

ADD_LIBRARY(share STATIC parse_magic.c get_binary_info.c print_error.c get_load_cmds.c del_binary_info.c get_load_cmds_mach_o_32.c get_load_cmds_mach_o_64.c)

target_link_libraries(share ft)
target_include_directories(share PUBLIC .)