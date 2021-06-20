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
	t_vec					*segments;
	struct symtab_command	symtab;

	binary_info = get_binary_info(path);
	if (!binary_info)
		return ;
	segments = get_segments(binary_info);
	if (!segments)
	{
		free_mem(&binary_info, &segments);
		return ;
	}
	if (!get_symtab_cmd(&symtab, binary_info))
		print_symtab(&symtab, segments, binary_info);
	else
		print_symtab(NULL, segments, binary_info);
	free_mem(&binary_info, &segments);
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
