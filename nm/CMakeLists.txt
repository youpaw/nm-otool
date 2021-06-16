cmake_minimum_required(VERSION 3.17)
project(nm C)

set(CMAKE_C_STANDARD 99)

add_executable(nm nm.c print_symtab.c mach-o/get_symtab_mach_o_32.c mach-o/get_sym_info_table_mach_o_32.c mach-o/get_sym_info_table_mach_o_64.c get_symbol_char.c cmp_sym_info.c mach-o/get_symtab_mach_o_64.c get_symtab_cmd.c)
target_link_libraries(nm ft_printf share)