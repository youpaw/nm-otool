//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"
#include "ft_mem.h"

static int	get_magic(t_binary_info *binary_info, int n_bin, int n_arch)
{
	size_t						magic_size;
	static const t_magic_map	magic_map[N_BIN_TYPES][N_ARCH_TYPES] = {
			{{e_32, 4, MH_MAGIC},
			{e_64, 4, MH_MAGIC_64}}
	};

	magic_size = magic_map[n_bin][n_arch].size;
	if (binary_info->archsize < magic_size)
		return (1);
	ft_memcpy(&binary_info->magic, binary_info->mapstart, magic_size);
	if (magic_map[n_bin][n_arch].magic == binary_info->magic)
		binary_info->swap = 0;
	else if (ft_swap_uint32(magic_map[n_bin][n_arch].magic) == \
		binary_info->magic)
		binary_info->swap = 1;
	else
		return (1);
	return (0);
}

int	parse_magic(t_binary_info *binary_info)
{
	int	n_bin;
	int	n_arch;

	n_bin = 0;
	while (n_bin < N_BIN_TYPES)
	{
		n_arch = -1;
		while (++n_arch < N_ARCH_TYPES)
			if (!get_magic(binary_info, n_bin, n_arch))
				break ;
		if (n_arch < N_ARCH_TYPES)
			break ;
		n_bin++;
	}
	if (n_bin < N_BIN_TYPES)
	{
		binary_info->arch = (t_arch_type)n_arch;
		binary_info->type = (t_bin_type)n_bin;
		errno = 0;
		return (0);
	}
	errno = E_NT_NTVLD;
	return (1);
}
