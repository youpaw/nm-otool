//
// Created by Darth Butterwell on 3/8/21.
//

#include "nm.h"

void print_symtab(t_symtab_cmd *symtab_cmd, t_vec *load_cmds, \
				  t_binary_info *binary_info)
{
	t_sym_info **(*print_symtab_handlers[N_BIN_TYPES][N_ARCH_TYPES]) \
	(void *, t_symtab_cmd *, t_vec *) = {
			{&get_sym_info_mach_o_32, &get_sym_info_mach_o_64}
	};

	print_symtab_handlers[binary_info->type][binary_info->arch]\
	(binary_info->map_start, symtab_cmd, load_cmds);
}
