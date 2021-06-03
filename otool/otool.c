//
// Created by Darth Butterwell on 3/7/21.
//

#include <printf.h>
#include "ft_env.h"
#include "otool.h"

static void print_usage(const char *name)
{
	printf("Usage: %s [-t] <object file> ...\n", name);
	printf("\t-t print the text section\n");
	errno = EINVAL;
}

static void free_mem(t_binary_info **binary_info, t_vec **load_cmds)
{
	if (binary_info)
		del_binary_info(binary_info);
	if (load_cmds)
		ft_vec_del(load_cmds);
}

static void exec(const char *path)
{
	t_binary_info 		*binary_info;
	t_vec				*load_cmds;

	binary_info = get_binary_info(path);
	if (!binary_info)
		return ;
	load_cmds = get_load_cmds(binary_info);
	if (!load_cmds)
	{
		free_mem(&binary_info, &load_cmds);
		return ;
	}
	print_text(load_cmds, binary_info);
	free_mem(&binary_info, &load_cmds);
}

int main(int ac, const char **av)
{
	if (ac < 3 && !ft_strcmp(av[1], "-t"))
		print_usage(av[0]);
	else
	{
		g_nc = 2;
		while (g_nc < ac)
		{
			exec(av[g_nc]);
			g_nc++;
		}
	}
	return (errno);
}