//
// Created by Darth Butterwell on 3/21/21.
//

#include "nm.h"
#include "ft_str.h"
#include "ft_char.h"

static char	get_section_char(uint8_t type, const char *sectname)
{
	static const t_sym_map	sym_map[N_SYM_MAP] = {
			{SECT_TEXT, 'T'}, {SECT_DATA, 'D'}, {SECT_BSS, 'B'}
	};
	uint8_t					cnt;

	cnt = 0;
	while (cnt < N_SYM_MAP)
	{
		if (!ft_strncmp(sym_map[cnt].sect_name, sectname, SYM_NAME_SIZE))
		{
			if (!(type & N_EXT))
				return ((char) ft_tolower(sym_map[cnt].sym));
			return (sym_map[cnt].sym);
		}
		cnt++;
	}
	if (!(type & N_EXT))
		return ('s');
	return ('S');
}

static char	get_known_char(uint8_t type_mask)
{
	if (type_mask & N_ABS)
		return ('A');
	else if (type_mask & N_PBUD)
		return ('Z');
	else if (type_mask & N_INDR)
		return ('i');
	else
		return ('U');
}

int	get_symbol_char(uint8_t type, uint8_t n_sect, const char *sectname, char *c)
{
	uint8_t			type_mask;

	if (n_sect != NO_SECT)
	{
		if (!sectname)
			return (1);
		*c = get_section_char(type, sectname);
	}
	else
	{
		type_mask = type & N_TYPE;
		*c = get_known_char(type_mask);
	}
	return (0);
}
