//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef NM_H
#define NM_H
#include "share.h"
#include <mach-o/nlist.h>
#define DEFAULT_FILE_PATH "a.out"

typedef struct	s_symbol_address{
	int		address;
	char	symbol;
}				t_symbol_address;

typedef struct symtab_command t_symtab_cmd;
typedef struct nlist_64 t_nlist_64;

t_symbol_address	**get_symbol_map(t_vec *load_cmds);
t_symtab_cmd		*get_symtab_cmd(t_vec *load_cmds);
void 				print_symtab(t_symbol_address **symbol_map, \
	t_symtab_cmd *symtab_cmd);

#endif //NM_H
