//
// Created by Darth Butterwell on 3/7/21.
//
#include "nm.h"
#include "ft_env.h"

static void	free_mem(t_binary_info **binary_info, t_vec **load_cmds)
{
	if (binary_info)
		del_binary_info(binary_info);
	if (load_cmds)
		ft_vec_del(load_cmds);
}

static void	exec(const char *path)
{
	t_binary_info			*binary_info;
	t_vec					*load_cmds;
	struct symtab_command	*symtab_cmd;

	binary_info = get_binary_info(path);
	if (!binary_info)
		return ;
	load_cmds = get_load_cmds(binary_info);
	if (!load_cmds)
	{
		free_mem(&binary_info, &load_cmds);
		return ;
	}
	symtab_cmd = get_symtab_cmd(load_cmds);
	print_symtab(symtab_cmd, load_cmds, binary_info);
	free_mem(&binary_info, &load_cmds);
}

int	main(int ac, const char **av)
{
	const char	*arg[2];

	if (ac < 2)
	{
		g_ac = 2;
		arg[0] = av[0];
		arg[1] = DEFAULT_FILE_PATH;
		g_av = arg;
	}
	g_nc = 1;
	while (g_nc < g_ac)
	{
		exec(g_av[g_nc]);
		g_nc++;
	}
	return (errno);
}
