//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef NM_H
#define NM_H
#include <mach-o/nlist.h>
#include "share.h"
#include "ft_str.h"
#define DEFAULT_FILE_PATH "a.out"

typedef struct symtab_command t_symtab_cmd;
typedef struct nlist t_nlist_32;
typedef struct nlist_64 t_nlist_64;

t_symtab_cmd		*get_symtab_cmd(t_vec *load_cmds);
void print_symtab(t_symtab_cmd *symtab_cmd, t_vec *load_cmds, \
					t_binary_info *binary_info);
void print_symtab_mach_o_32(t_nlist_32 *sym_table, char *str_table, \
	uint32_t n_syms, t_vec *load_cmds);
void print_symtab_mach_o_64(t_nlist_64 *sym_table, char *str_table, \
	uint32_t n_syms, t_vec *load_cmds);

#endif //NM_H
