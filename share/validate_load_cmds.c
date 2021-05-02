//
// Created by Darth Butterwell on 5/2/21.
//

#include "share.h"

int validate_load_cmds(t_load_cmd *lc, size_t bin_size, t_check_sizes *check)
{
	if ((bin_size < (check->full + sizeof(t_load_cmd))) || \
		(bin_size < (check->full + lc->cmdsize)))
		return (1);
	check->cmds += lc->cmdsize;
	check->full += lc->cmdsize;
	return (0);
}