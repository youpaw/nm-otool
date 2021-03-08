cmake_minimum_required(VERSION 3.17)
project(nm C)

set(CMAKE_C_STANDARD 99)

add_executable(nm nm.c get_symbol_map.c print_symtab.c get_symtab_cmd.c)
target_link_libraries(nm ft share)