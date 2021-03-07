//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"
#include <ft_mem.h>

const t_magick_map g_magick_map[N_BIN_TYPES][N_ARCH_TYPES] = {
		{{e_32, {MH_MAGIC, MH_CIGAM}},
		{e_64, {MH_MAGIC_64, MH_CIGAM_64}}}
};

int		parse_magick(t_binary_info *binary_info)
{
	uint32_t magick;
	int n_bin;
	int n_arch;
	int n_magick;

	ft_memcpy(&magick, binary_info->map_start, sizeof(uint32_t));
	n_bin = -1;
	while (++n_bin < N_BIN_TYPES)
	{
		n_arch = -1;
		while (++n_arch < N_ARCH_TYPES)
		{
			n_magick = -1;
			while (++n_magick < N_MAGICK_NUMBERS)
			{
				if (g_magick_map[N_BIN_TYPES][N_ARCH_TYPES]\
				.magick[N_MAGICK_NUMBERS] == magick)
			}
		}
	}
	return (0);
}