//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"
#include "ft_mem.h"

static int get_magic(t_binary_info *binary_info, int n_bin, int n_arch)
{
	int							n_magic;
	size_t						magic_size;
	static const t_magic_map	magic_map[N_BIN_TYPES][N_ARCH_TYPES] = {
			{{e_32, 4, {MH_MAGIC, MH_CIGAM}},
			{e_64, 4, {MH_MAGIC_64, MH_CIGAM_64}}}
	};

	n_magic = 0;
	while (n_magic < N_MAGIC_NUMBERS)
	{
		magic_size = magic_map[n_bin][n_arch].size;
		if (binary_info->file_stat.st_size < magic_size)
			return (1);
		ft_memcpy(&binary_info->magic, binary_info->map_start, magic_size);
		if (magic_map[n_bin][n_arch].magic[n_magic] == binary_info->magic)
			return (0);
		n_magic++;
	}
	return (1);
}

int		parse_magic(t_binary_info *binary_info)
{
	int		n_bin;
	int		n_arch;

	n_bin = 0;
	while (n_bin < N_BIN_TYPES)
	{
		n_arch = 0;
		while (n_arch < N_ARCH_TYPES)
		{
			if (!get_magic(binary_info, n_bin, n_arch))
				break;
			n_arch++;
		}
		if (n_arch < N_ARCH_TYPES)
			break ;
		n_bin++;
	}
	if (n_bin < N_BIN_TYPES)
	{
		binary_info->arch = (t_arch_type)n_arch;
		binary_info->type = (t_bin_type)n_bin;
		return (0);
	}
	g_error_code = MAGIC_ERROR;
	return (1);
}