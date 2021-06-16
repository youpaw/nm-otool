//
// Created by Darth Butterwell on 6/14/21.
//

#include "share.h"
#include "ft_mem.h"

int	get_header_fat(struct fat_header *fat_header, \
	t_binary_info *binary_info)
{
	struct fat_header	*header_ptr;

	if (binary_info->size < sizeof(struct fat_header))
	{
		errno = E_NT_TRMLF;
		return (errno);
	}
	header_ptr = (struct fat_header *) binary_info->mapstart;
	if (binary_info->swap)
		fat_header->nfat_arch = ft_swap_uint32(header_ptr->nfat_arch);
	else
		fat_header->nfat_arch = header_ptr->nfat_arch;
	fat_header->magic = header_ptr->magic;
	return (0);
}
