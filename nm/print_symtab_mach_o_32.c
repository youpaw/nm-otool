//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"

void	print_symtab_mach_o_32(t_nlist_32 *sym_table, char *str_table, \
	uint32_t n_syms, t_vec *load_cmds)
{
	uint32_t syms_cnt;

	syms_cnt = 0;
	while (syms_cnt < n_syms)
	{
		sym_table = (t_nlist_32 *)((char *)sym_table + sizeof(t_nlist_32));
		str_table += ft_strlen(str_table) + 1;
		syms_cnt++;
	}
}