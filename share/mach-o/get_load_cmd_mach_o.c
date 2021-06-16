//
// Created by Darth Butterwell on 6/16/21.
//

#include "share.h"
#include "ft_mem.h"

int	get_load_cmd(struct load_command *load_command, \
	t_binary_info *binary_info, size_t mapoff)
{
	struct load_command	*ld_cmd_ptr;

	if (binary_info->archsize < mapoff + sizeof(struct load_command))
		return (1);
	ld_cmd_ptr = (struct load_command *)((char *)binary_info->mapstart + \
		mapoff);
	if (binary_info->swap)
	{
		load_command->cmd = ft_swap_uint32(ld_cmd_ptr->cmd);
		load_command->cmdsize = ft_swap_uint32(ld_cmd_ptr->cmdsize);
	}
	else
	{
		load_command->cmd = ld_cmd_ptr->cmd;
		load_command->cmdsize = ld_cmd_ptr->cmdsize;
	}
	if (binary_info->archsize < (mapoff + load_command->cmdsize) || \
		load_command->cmdsize < sizeof(struct load_command))
		return (1);
	return (0);
}
