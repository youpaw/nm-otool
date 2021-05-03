//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"
#include "ft_mem.h"
#include "ft_arr.h"

static t_sym_info *get_sym_info(t_sym_tab *sym_tab, t_vec *sects)
{
	t_sym_info		*sym_info;
	t_nlist_32 		*sym_table;
	char			*str_table;

	sym_table = (t_nlist_32*) sym_tab->tab;
	str_table = sym_tab->str_tab;
	sym_info = (t_sym_info *) ft_xmalloc(sizeof(t_sym_info));
	sym_info->value = (size_t) sym_table->n_value;
	sym_info->nsect = sym_table->n_sect;
	sym_info->ntype = sym_table->n_type;
	sym_info->c = get_symbol_char(sym_table->n_type, sym_table->n_sect, sects);
	//Todo get_symbol_char might return error
	sym_info->str = str_table + sym_table->n_un.n_strx;
	return (sym_info);
}

static int			get_sym_tab(t_binary_info *bin_info, \
	t_symtab_cmd *symtab_cmd, t_sym_tab *sym_tab)
{
	size_t		sym_table_size;
	size_t		file_size;

	file_size = bin_info->file_stat.st_size;
	sym_table_size = sizeof(t_nlist_32);
	if (file_size < symtab_cmd->symoff || \
		file_size < symtab_cmd->stroff || \
		file_size < (symtab_cmd->symoff + (symtab_cmd->nsyms * sym_table_size)))
		return (1);
	sym_tab->tab = (char *) bin_info->map_start + symtab_cmd->symoff;
	sym_tab->str_tab = (char *) bin_info->map_start + symtab_cmd->stroff;
	return (0);
}

t_sym_info **get_sym_info_table_mach_o_32(t_binary_info *binary_info, \
	t_symtab_cmd *symtab_cmd, t_vec *load_cmds)
{
	t_sym_info	**sym_info_table;
	t_sym_tab	sym_tab;
	uint32_t	syms_cnt;
	t_vec		*sects;
	size_t		tab_size;

	if (!(sects = get_sections_mach_o_32(load_cmds)))
		return (NULL);
	sym_info_table = (t_sym_info **) ft_xmalloc(sizeof(t_sym_info*) * \
		symtab_cmd->nsyms);
	tab_size = sizeof(t_nlist_32);
	syms_cnt = -1;
	if (!get_sym_tab(binary_info, symtab_cmd, &sym_tab))
	{
		while (++syms_cnt < symtab_cmd->nsyms)
		{
			if (!(sym_info_table[syms_cnt] = get_sym_info(&sym_tab, sects)))
				break ;
			sym_tab.tab = (void *) ((char *) sym_tab.tab + tab_size);
		}
	}
	if (syms_cnt < symtab_cmd->nsyms)
		ft_narr_del((void **) sym_info_table, symtab_cmd->nsyms, NULL); //Todo write Null to pointer in narrdel
	ft_vec_del(&sects);
	return (sym_info_table);
}