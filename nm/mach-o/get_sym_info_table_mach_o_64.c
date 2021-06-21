//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"
#include "ft_mem.h"
#include "ft_arr.h"

static int	get_sectname(char sectname[SECTNAME_SIZE], uint8_t n_sect, \
	t_vec *sects)
{
	struct section_64	sect;

	if (n_sect != NO_SECT)
	{
		if (!ft_vec_get_at(&sect, sects, n_sect - 1))
			ft_memcpy(sectname, sect.sectname, SECTNAME_SIZE);
		else
			return (1);
	}
	return (0);
}

static t_sym_info	*get_sym_info(struct nlist_64 *nlist, char *strtab, \
	t_vec *sects, size_t strsize)
{
	t_sym_info	*sym_info;
	char		sectname[SECTNAME_SIZE];
	char		c;

	if (get_sectname(sectname, nlist->n_sect, sects))
		print_nt_error(E_NT_TRMLF);
	else if (get_symbol_char(nlist->n_type, nlist->n_sect, sectname, &c))
		print_nt_error(E_NT_TRMLF);
	else
	{
		sym_info = (t_sym_info *) ft_xmalloc(sizeof(t_sym_info));
		sym_info->value = (size_t) nlist->n_value;
		sym_info->nsect = nlist->n_sect;
		sym_info->ntype = nlist->n_type;
		sym_info->c = c;
		if (strsize < nlist->n_un.n_strx)
			sym_info->str = BAD_STRING_INDEX;
		else
			sym_info->str = strtab + nlist->n_un.n_strx;
		return (sym_info);
	}
	return (NULL);
}

static t_sym_info	**get_sym_info_table(t_vec *sects, t_vec *nlists, \
	char *strtab, size_t strsize)
{
	struct nlist_64	nlist;
	t_sym_info		**sym_info_table;
	uint32_t		cnt;

	sym_info_table = (t_sym_info **) ft_xmalloc(sizeof(t_sym_info *) * \
		nlists->size);
	cnt = 0;
	while (cnt < nlists->size)
	{
		ft_vec_get_at(&nlist, nlists, cnt);
		sym_info_table[cnt] = get_sym_info(&nlist, strtab, sects, strsize);
		if (!sym_info_table[cnt])
			break ;
		cnt++;
	}
	if (cnt < nlists->size)
		ft_narr_del((void ***) &sym_info_table, cnt, NULL);
	return (sym_info_table);
}

t_sym_info	**get_sym_info_table_mach_o_64(t_binary_info *binary_info, \
	struct symtab_command *symtab_cmd, t_vec *load_cmds)
{
	t_sym_info	**sym_info_table;
	t_vec		*sects;
	t_vec		*nlists;

	sects = get_sections_mach_o_64(load_cmds, binary_info);
	if (!sects)
		return (NULL);
	sym_info_table = NULL;
	nlists = get_nlists_mach_o_64(symtab_cmd, binary_info);
	if ((binary_info->archoff + binary_info->archsize) < \
		(symtab_cmd->stroff + symtab_cmd->strsize))
		print_nt_error(E_NT_TRMLF);
	else if (nlists)
		sym_info_table = get_sym_info_table(sects, nlists, \
			binary_info->mapstart + symtab_cmd->stroff, symtab_cmd->strsize);
	ft_vec_del(&sects);
	ft_vec_del(&nlists);
	return (sym_info_table);
}
