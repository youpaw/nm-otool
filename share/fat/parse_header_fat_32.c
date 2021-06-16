//
// Created by Darth Butterwell on 6/10/21.
//

#include "share.h"
#include "ft_mem.h"

static int	get_arch(struct fat_arch *arch, t_binary_info *bin_info, \
	size_t mapoff)
{
	struct fat_arch	*arch_ptr;

	if (bin_info->size < mapoff + sizeof(struct fat_arch))
		return (1);
	arch_ptr = (struct fat_arch *)((char *)bin_info->mapstart + mapoff);
	if (bin_info->swap)
	{
		arch->cputype = ft_swap_int32(arch_ptr->cputype);
		arch->cpusubtype = ft_swap_int32(arch_ptr->cpusubtype);
		arch->offset = ft_swap_uint32(arch_ptr->offset);
		arch->size = ft_swap_uint32(arch_ptr->size);
	}
	else
	{
		arch->cputype = arch_ptr->cputype;
		arch->cpusubtype = arch_ptr->cpusubtype;
		arch->offset = arch_ptr->offset;
		arch->size = arch_ptr->size;
	}
	return (0);
}

static int	find_arch(struct fat_arch *arch, struct fat_header *header, \
	t_binary_info *bin_info)
{
	size_t			narch;
	size_t			mapoff;

	mapoff = sizeof(struct fat_header);
	narch = 0;
	while (narch < header->nfat_arch)
	{
		if (get_arch(arch, bin_info, mapoff) || \
			bin_info->size < arch->offset + arch->size)
		{
			errno = E_NT_TRMLF;
			return (1);
		}
		if (arch->cputype == CPU_TYPE_X86_64 && \
			(arch->cpusubtype & ~CPU_SUBTYPE_MASK) == CPU_SUBTYPE_X86_ALL)
			return (0);
		mapoff += sizeof(struct fat_arch);
		narch++;
	}
	errno = E_NT_NTVLD;
	return (1);
}

int	parse_header_fat_32(t_binary_info *binary_info)
{
	struct fat_header	header;
	struct fat_arch		arch;

	if (get_header_fat(&header, binary_info))
		return (1);
	if (find_arch(&arch, &header, binary_info))
		return (1);
	binary_info->mapstart = (char *)binary_info->mapstart + arch.offset;
	binary_info->archoff = arch.offset;
	binary_info->archsize = arch.size;
	return (parse_magic(binary_info));
}
