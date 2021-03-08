//
// Created by Darth Butterwell on 3/7/21.
//
#include "nm.h"

static void free_mem(t_binary_info **binary_info, t_vec **load_cmds, \
	t_symbol_address ***symbol_map)
{
	if (binary_info)
		del_binary_info(binary_info);
	if (load_cmds)
		ft_vec_del(load_cmds);
	if (symbol_map)
		free(*symbol_map); //maybe
}

static void exec(const char *name, const char *path)
{
	t_binary_info 		*binary_info;
	t_vec				*load_cmds;
	t_symtab_cmd		*symtab_cmd;
	t_symbol_address 	**symbol_map;

	symbol_map = NULL;
	if (!(binary_info = get_binary_info(path)))
	{
		print_error(name, path);
		return ;
	}
	load_cmds = get_load_cmds(binary_info, -1);
	if ((symtab_cmd = get_symtab_cmd(load_cmds)))
		symbol_map = get_symbol_map(load_cmds);
	print_symtab(symbol_map, symtab_cmd);
	free_mem(&binary_info, &load_cmds, &symbol_map); //maybe
}

int main(int ac, const char **av)
{
	int		index;

	if (ac < 2)
	{
		print_error(av[0], DEFAULT_FILE_PATH);
	}
	else
	{
		index = 1;
		while (index < ac)
		{
			exec(av[0], av[index]);
			index++;
		}
	}
	return g_error_code;
}