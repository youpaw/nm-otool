//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"
#include "ft_mem.h"
#include "ft_arr.h"

static t_sym_info	*get_sym_info(t_nlist_64 *sym_table, char *str_table, \
	uint32_t stroff, size_t file_size, t_vec *sects)
{
	t_sym_info		*sym_info;
	char			c;

	if (file_size < (stroff + sym_table->n_un.n_strx))
		errno = E_NT_TRMLF;
	else if (get_symbol_char(sym_table->n_type, sym_table->n_sect, sects, &c))
		errno = E_NT_TRMLF;
	else
	{
		sym_info = (t_sym_info *) ft_xmalloc(sizeof(t_sym_info));
		sym_info->value = (size_t) sym_table->n_value;
		sym_info->nsect = sym_table->n_sect;
		sym_info->ntype = sym_table->n_type;
		sym_info->c = c;
		sym_info->str = str_table + sym_table->n_un.n_strx;
		return (sym_info);
	}
	return (NULL);
}

static int			get_sym_tab(t_binary_info *bin_info, \
	t_symtab_cmd *symtab_cmd, t_sym_tab *sym_tab)
{
	size_t			file_size;

	file_size = bin_info->file_stat.st_size;
	if (file_size < (symtab_cmd->symoff + \
		(symtab_cmd->nsyms * sizeof(t_nlist_64))))
		errno = E_NT_TRMLF;
	else if (file_size < (symtab_cmd->stroff + symtab_cmd->strsize))
		errno = E_NT_TRMLF;
	else
	{
		sym_tab->tab = (char *) bin_info->map_start + symtab_cmd->symoff;
		sym_tab->str_tab = (char *) bin_info->map_start + symtab_cmd->stroff;
	}
	return (errno);
}

t_sym_info			**get_sym_info_table_mach_o_64(t_binary_info *binary_info, \
	t_symtab_cmd *symtab_cmd, t_vec *load_cmds)
{
	t_sym_info		**sym_info_table;
	t_sym_tab		stab;
	uint32_t		cnt;
	t_vec			*sects;

	sects = get_sections_mach_o_64(load_cmds);
	if (!sects)
		return (NULL);
	sym_info_table = (t_sym_info **) ft_xmalloc(sizeof(t_sym_info*) * \
		symtab_cmd->nsyms);
	cnt = 0;
	if (!get_sym_tab(binary_info, symtab_cmd, &stab))
		while (cnt < symtab_cmd->nsyms)
		{
			sym_info_table[cnt] = get_sym_info(stab.tab, stab.str_tab,\
			symtab_cmd->stroff, binary_info->file_stat.st_size, sects);
			if (!sym_info_table[cnt])
				break ;
			stab.tab = (void *) ((char *) stab.tab + sizeof(t_nlist_64));
			cnt++;
		}
	if (cnt < symtab_cmd->nsyms)
		ft_narr_del((void ***) &sym_info_table, symtab_cmd->nsyms, NULL);
	ft_vec_del(&sects);
	return (sym_info_table);
}
