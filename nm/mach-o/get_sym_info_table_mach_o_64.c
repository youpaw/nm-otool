//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"
#include "ft_mem.h"

static t_sym_info *get_sym_info(t_nlist_64 *sym_table, char *str_table, \
	t_vec *sects)
{
	t_sym_info		*sym_info;

	sym_info = (t_sym_info *) ft_xmalloc(sizeof(t_sym_info));
	sym_info->value = (size_t) sym_table->n_value;
	sym_info->nsect = sym_table->n_sect;
	sym_info->ntype = sym_table->n_type;
	sym_info->c = get_symbol_char(sym_table->n_type, sym_table->n_sect, sects);
	sym_info->str = str_table + sym_table->n_un.n_strx;
	return (sym_info);
}

t_sym_info **get_sym_info_table_mach_o_64(t_binary_info *binary_info, \
	t_symtab_cmd *symtab_cmd, t_vec *load_cmds)
{
	t_sym_info	**sym_info_table;
	t_nlist_64	*sym_table;
	char		*str_table;
	uint32_t	syms_cnt;
	t_vec		*sects;
	//Todo copy 32-bit
	if (!(get_sections_mach_o_64(load_cmds)))
		return (NULL);
	sym_info_table = (t_sym_info **) ft_xmalloc(sizeof(t_sym_info*) * \
	symtab_cmd->nsyms);
	sym_table = (t_nlist_64 *) ((char *) binary_info + symtab_cmd->symoff);
	str_table = (char *) binary_info + symtab_cmd->stroff;
	syms_cnt = 0;
	while (syms_cnt < symtab_cmd->nsyms)
	{
		sym_info_table[syms_cnt] = get_sym_info(sym_table, str_table, sects);
		sym_table = (t_nlist_64 *)((char *)sym_table + sizeof(t_nlist_64));
		syms_cnt++;
	}
	ft_vec_del(&sects);
	return (sym_info_table);
}