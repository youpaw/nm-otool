//
// Created by Darth Butterwell on 6/16/21.
//

#include "share.h"
#include "ft_mem.h"

int	get_header_mach_o_64(struct mach_header_64 *header, \
	t_binary_info *binary_info)
{
	struct mach_header_64	*header_ptr;

	if (binary_info->archsize < sizeof(struct mach_header_64))
		return (1);
	header_ptr = (struct mach_header_64 *) binary_info->mapstart;
	header->magic = header_ptr->magic;
	if (binary_info->swap)
	{
		header->ncmds = ft_swap_uint32(header_ptr->ncmds);
		header->sizeofcmds = ft_swap_uint32(header_ptr->sizeofcmds);
	}
	else
	{
		header->ncmds = header_ptr->ncmds;
		header->sizeofcmds = header_ptr->sizeofcmds;
	}
	return (0);
}
