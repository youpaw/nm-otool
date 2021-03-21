//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef NM_H
#define NM_H
#include <mach-o/nlist.h>
#include "share.h"
#define DEFAULT_FILE_PATH "a.out"
#define SECTIONS_VEC_CAPACITY 20

typedef struct	s_sym_info{
	size_t	value;
	char	c;
	char	*str;
}				t_sym_info;

typedef struct symtab_command t_symtab_cmd;
typedef struct nlist t_nlist_32;
typedef struct nlist_64 t_nlist_64;

t_symtab_cmd		*get_symtab_cmd(t_vec *load_cmds);

void print_symtab(t_symtab_cmd *symtab_cmd, t_vec *load_cmds, \
					t_binary_info *binary_info);

char get_symbol_char(uint8_t type, char *sect_name);

t_sym_info **get_sym_info_mach_o_32(void *map_start, t_symtab_cmd *symtab_cmd, \
	t_vec *load_cmds);

t_sym_info **get_sym_info_mach_o_64(void *map_start, t_symtab_cmd *symtab_cmd, \
	t_vec *load_cmds);

#endif //NM_H
