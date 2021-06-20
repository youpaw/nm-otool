//
// Created by Darth Butterwell on 6/16/21.
//

#include "nm.h"

int (*g_symtab_parser_handlers[N_BIN_TYPES][N_ARCH_TYPES]) \
	(struct symtab_command *, t_binary_info *) = {
		{&get_symtab_cmd_mach_o_32, &get_symtab_cmd_mach_o_64}
};

int	get_symtab_cmd(struct symtab_command *symtab, t_binary_info *binary_info)
{
	return (g_symtab_parser_handlers[binary_info->type][binary_info->arch] \
		(symtab, binary_info));
}
