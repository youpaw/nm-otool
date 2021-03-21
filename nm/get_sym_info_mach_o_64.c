//
// Created by Darth Butterwell on 3/20/21.
//

#include "nm.h"
#include "ft_mem.h"

static t_vec *get_sections(t_vec *load_cmds)
{
	t_load_cmd			*lc;
	t_segment_cmd_64	*seg;
	t_section_64		*sect;
	size_t				cnt[2];
	t_vec				*sections;

	sections = ft_vec_new(SECTIONS_VEC_CAPACITY, sizeof(void *), NULL);
	cnt[0] = -1;
	while (++cnt[0] < load_cmds->size)
	{
		ft_vec_get_at(&lc, load_cmds, cnt[0]);
		if (lc->cmd == LC_SEGMENT_64)
			seg = (t_segment_cmd_64 *) lc;
		else
			continue ;
		cnt[1] = -1;
		sect = (t_section_64 *) ((char *) seg + sizeof(t_segment_cmd_64));
		while (++cnt[1] < seg->nsects)
		{
			ft_vec_push(sections, &sect);
			sect = (t_section_64 *) ((char *) sect + sizeof(t_section_64));
		}
	}
	return (sections);
}

static t_sym_info *get_sym_info(t_nlist_64 *sym_table, char *str_table, \
	t_vec *sections)
{
	t_sym_info		*sym_info;
	t_section_64	*sect;
	char			*sect_name;

	sym_info = (t_sym_info *) ft_xmalloc(sizeof(t_sym_info));
	sym_info->value = (size_t) sym_table->n_value;
	if (sym_table->n_sect != NO_SECT)
	{
		ft_vec_get_at(&sect, sections, sym_table->n_sect);
		sect_name = sect->sectname;
	}
	else
		sect_name = NULL;
	sym_info->c = get_symbol_char(sym_table->n_type, sect_name);
	sym_info->str = str_table + sym_table->n_un.n_strx;
	return (sym_info);
}

t_sym_info **get_sym_info_mach_o_64(void *map_start, t_symtab_cmd *symtab_cmd, \
	t_vec *load_cmds)
{
	t_sym_info	**sym_info_table;
	t_nlist_64	*sym_table;
	char		*str_table;
	uint32_t	syms_cnt;
	t_vec		*sections;

	sym_info_table = (t_sym_info **) ft_xmalloc(sizeof(t_sym_info*) * symtab_cmd->nsyms);
	sections = get_sections(load_cmds);
	sym_table = (t_nlist_64 *) ((char *) map_start + symtab_cmd->symoff);
	str_table = (char *) map_start + symtab_cmd->stroff;
	syms_cnt = 0;
	while (syms_cnt < symtab_cmd->nsyms)
	{
		sym_info_table[syms_cnt] = get_sym_info(sym_table, str_table, sections);
		sym_table = (t_nlist_64 *)((char *)sym_table + sizeof(t_nlist_64));
		syms_cnt++;
	}
	ft_vec_del(&sections);
	return (sym_info_table);
}