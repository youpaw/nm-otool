//
// Created by Darth Butterwell on 3/8/21.
//

#include "nm.h"
#include "ft_arr.h"
#include <stdio.h>

static void print_sym_info_table(t_sym_info **sym_info_table, uint32_t nsyms)
{
	uint32_t cnt;

	cnt = 0;
	while (cnt < nsyms)
	{
		if (sym_info_table[cnt]->nsect == NO_SECT)
			printf("%16s %c %s\n", "", sym_info_table[cnt]->c, \
				sym_info_table[cnt]->str);
		else
			printf("%016zx %c %s\n", sym_info_table[cnt]->value, \
				sym_info_table[cnt]->c, sym_info_table[cnt]->str);
		cnt++;
	}
}

void print_symtab(t_symtab_cmd *symtab_cmd, t_vec *load_cmds, \
				  t_binary_info *binary_info)
{
	static t_sym_info	**(*sym_info_handlers[N_BIN_TYPES][N_ARCH_TYPES])\
	(void *, t_symtab_cmd *, t_vec *) = {
			{&get_sym_info_table_mach_o_32, &get_sym_info_table_mach_o_64}
	};
	t_sym_info **sym_info_table;

	sym_info_table = sym_info_handlers[binary_info->type][binary_info->arch]\
		(binary_info->map_start, symtab_cmd, load_cmds);
	print_sym_info_table(sym_info_table, symtab_cmd->nsyms);
	ft_narr_del((void **) sym_info_table, symtab_cmd->nsyms, NULL);
}
