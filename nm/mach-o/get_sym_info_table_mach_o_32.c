//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"
#include "ft_mem.h"
#include "ft_arr.h"

static const char	*get_sectname(uint8_t n_sect, t_vec *sects)
{
	struct section	*sect;

	if (n_sect != NO_SECT)
	{
		if (!ft_vec_get_at(&sect, sects, n_sect - 1))
			return (sect->sectname);
	}
	return (NULL);
}

static t_sym_info	*get_sym_info(t_sym_tab *stab, uint32_t stroff, \
	size_t file_size, t_vec *sects)
{
	t_sym_info		*sym_info;
	struct nlist	*sym_table;
	char			*str_table;
	char			c;

	sym_table = stab->tab;
	str_table = stab->strtab;
	if (file_size < (stroff + sym_table->n_un.n_strx))
		print_nt_error(E_NT_TRMLF);
	else if (get_symbol_char(sym_table->n_type, sym_table->n_sect, \
		get_sectname(sym_table->n_sect, sects), &c))
		print_nt_error(E_NT_TRMLF);
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

static int	get_sym_tab(t_binary_info *bin_info, \
	struct symtab_command *symtab_cmd, t_sym_tab *sym_tab)
{
	size_t	file_size;

	file_size = bin_info->size;
	if (file_size < (symtab_cmd->symoff + \
		(symtab_cmd->nsyms * sizeof(struct nlist))))
		return (print_nt_error(E_NT_TRMLF));
	else if (file_size < (symtab_cmd->stroff + symtab_cmd->strsize))
		return (print_nt_error(E_NT_TRMLF));
	else
	{
		sym_tab->tab = (char *) bin_info->mapstart + symtab_cmd->symoff;
		sym_tab->strtab = (char *) bin_info->mapstart + symtab_cmd->stroff;
	}
	return (0);
}

static t_sym_info	**get_sym_info_table(t_binary_info *binary_info, \
	struct symtab_command *symtab_cmd, t_sym_tab *stab, t_vec *sects)
{
	t_sym_info	**sym_info_table;
	uint32_t	cnt;

	sym_info_table = (t_sym_info **) ft_xmalloc(sizeof(t_sym_info *) * \
		symtab_cmd->nsyms);
	cnt = 0;
	while (cnt < symtab_cmd->nsyms)
	{
		sym_info_table[cnt] = get_sym_info(stab, symtab_cmd->stroff, \
			binary_info->size, sects);
		if (!sym_info_table[cnt])
			break ;
		stab->tab = (void *)((char *) stab->tab + sizeof(struct nlist));
		cnt++;
	}
	if (cnt < symtab_cmd->nsyms)
		ft_narr_del((void ***) &sym_info_table, cnt, NULL);
	return (sym_info_table);
}

t_sym_info	**get_sym_info_table_mach_o_32(t_binary_info *binary_info, \
	struct symtab_command *symtab_cmd, t_vec *load_cmds)
{
	t_sym_info	**sym_info_table;
	t_sym_tab	stab;
	t_vec		*sects;

	sects = get_sections_mach_o_32(load_cmds, binary_info);
	if (!sects)
		return (NULL);
	sym_info_table = NULL;
	if (!get_sym_tab(binary_info, symtab_cmd, &stab))
		sym_info_table = get_sym_info_table(binary_info, symtab_cmd, &stab, \
			sects);
	ft_vec_del(&sects);
	return (sym_info_table);
}
