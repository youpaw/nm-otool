//
// Created by Darth Butterwell on 3/7/21.
//
#include "nm.h"

static void free_mem(t_binary_info **binary_info, t_vec **load_cmds)
{
	if (binary_info)
		del_binary_info(binary_info);
	if (load_cmds)
		ft_vec_del(load_cmds);
}

static int exec(const char *name, const char *path)
{
	t_binary_info 		*binary_info;
	t_vec				*load_cmds;
	t_symtab_cmd		*symtab_cmd;

	binary_info = get_binary_info(path);
	if (!binary_info)
		return (print_nt_error(name, path));
	load_cmds = get_load_cmds(binary_info);
	if (!load_cmds)
	{
		free_mem(&binary_info, &load_cmds);
		return (print_nt_error(name, path));
	}
	symtab_cmd = get_symtab_cmd(load_cmds);
	if (symtab_cmd)
		if (print_symtab(symtab_cmd, load_cmds, binary_info))
			print_nt_error(name, path);
	free_mem(&binary_info, &load_cmds);
	return (errno);
}

int main(int ac, const char **av)
{
	int		index;

	if (ac < 2)
	{
		exec(av[0], DEFAULT_FILE_PATH);
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
	return (errno);
}