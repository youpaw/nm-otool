cmake_minimum_required(VERSION 3.17)
project(nm C)

set(CMAKE_C_STANDARD 99)

add_executable(nm nm.c print_symtab.c get_symtab_cmd.c print_symtab_mach_o_32.c print_symtab_mach_o_64.c)
target_link_libraries(nm ft share)