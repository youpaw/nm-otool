//
// Created by Darth Butterwell on 3/8/21.
//

#include "nm.h"

t_symtab_cmd		*get_symtab_cmd(t_vec *load_cmds)
{
	size_t			index;
	t_load_cmd		*load_cmd;

	index = 0;
	while (index < load_cmds->size)
	{
		ft_vec_get_at(&load_cmd, load_cmds, index);
		if (load_cmd->cmd == LC_SYMTAB)
			return ((t_symtab_cmd *)load_cmd);
		index++;
	}
	return (NULL);
}