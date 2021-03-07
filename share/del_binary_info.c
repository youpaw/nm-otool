//
// Created by Darth Butterwell on 3/7/21.
//

#include <unistd.h>
#include "share.h"

static void 	free_binary_info_contents(t_binary_info *binary_info)
{
	munmap(binary_info->map_start, binary_info->file_stat.st_size);
	close(binary_info->fd);
}

void 			del_binary_info(t_binary_info **binary_info)
{
	if (binary_info && *binary_info)
	{
		free_binary_info_contents(*binary_info);
		free(*binary_info);
	}
}