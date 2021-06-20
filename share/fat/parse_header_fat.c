//
// Created by Darth Butterwell on 6/10/21.
//

#include "share.h"
#include "ft_mem.h"

static int	get_magic(t_binary_info *binary_info, int n_arch)
{
	size_t						magic_size;
	static const t_magic_map	magic_map[N_ARCH_TYPES] = {
			{e_32, 4, FAT_MAGIC},
			{e_64, 4, FAT_MAGIC_64}
	};

	magic_size = magic_map[n_arch].size;
	if (binary_info->size < magic_size)
		return (1);
	ft_memcpy(&binary_info->magic, binary_info->mapstart, magic_size);
	if (magic_map[n_arch].magic == binary_info->magic)
	{
		binary_info->swap = 0;
		return (0);
	}
	if (ft_swap_uint32(magic_map[n_arch].magic) == binary_info->magic)
	{
		binary_info->swap = 1;
		return (0);
	}
	return (1);
}

int	parse_header_fat(t_binary_info *binary_info)
{
	static	int	(*fat_parser[N_ARCH_TYPES])(t_binary_info *) = \
		{&parse_header_fat_32, &parse_header_fat_64};
	int			n_arch;

	n_arch = 0;
	while (n_arch < N_ARCH_TYPES)
	{
		if (!get_magic(binary_info, n_arch))
			return (fat_parser[n_arch](binary_info));
		n_arch++;
	}
	return (1);
}
