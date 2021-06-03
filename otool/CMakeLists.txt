cmake_minimum_required(VERSION 3.17)
project(otool C)

set(CMAKE_C_STANDARD 99)

add_executable(otool otool.c otool.h print_text.c mach-o/get_section_content_mach_o_32.c mach-o/get_section_content_mach_o_64.c)
target_link_libraries(otool ft share)