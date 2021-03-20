//
// Created by Darth Butterwell on 3/8/21.
//

#include "nm.h"

void print_symtab(t_symtab_cmd *symtab_cmd, t_vec *load_cmds, \
				  t_binary_info *binary_info)
{
	void (*print_symtab_handlers[N_BIN_TYPES][N_ARCH_TYPES]) \
	(void *, char *, uint32_t, t_vec *) = {
			{&print_symtab_mach_o_32, &print_symtab_mach_o_64}
	};
	void	*sym_table;
	char	*str_table;

	//TODO maybe add check for str_sice (symtab_cmd->str_size)
	sym_table = (char *)binary_info->map_start + symtab_cmd->symoff;
	str_table = (char *)binary_info->map_start + symtab_cmd->stroff;
	print_symtab_handlers[binary_info->type][binary_info->arch]\
	(sym_table, str_table, symtab_cmd->nsyms, load_cmds);
}
