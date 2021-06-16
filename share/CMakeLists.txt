cmake_minimum_required(VERSION 3.17)
project(share C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

ADD_LIBRARY(share STATIC parse_magic.c get_binary_info.c print_nt_error.c get_segments.c del_binary_info.c mach-o/get_segments_mach_o_32.c mach-o/get_segments_mach_o_64.c mach-o/get_sections_mach_o_32.c mach-o/get_sections_mach_o_64.c print_hexdump.c fat/parse_header_fat.c fat/parse_header_fat_32.c fat/parse_header_fat_64.c fat/get_header_fat.c mach-o/get_header_mach_o_32.c mach-o/get_header_mach_o_64.c mach-o/get_load_cmd_mach_o.c)

target_link_libraries(share ft_printf)
target_include_directories(share PUBLIC .)