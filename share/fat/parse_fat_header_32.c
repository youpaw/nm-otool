//
// Created by Darth Butterwell on 6/10/21.
//

#include <mach-o/fat.h>
#include "share.h"


static struct fat_header	*get_header(void *map_start, size_t bin_size)
{
	struct fat_header	*header;

	if (bin_size < sizeof(struct fat_header))
	{
		errno = E_NT_TRMLF;
		return (NULL);
	}
	header = (struct fat_header *) map_start;
	return (header);
}

static struct fat_arch	*get_arch(struct fat_header *header, size_t bin_size)
{
	struct fat_arch	*arch;
	size_t			n_arch;
	size_t			full_size;

	full_size = sizeof(struct fat_header);
	arch = (struct fat_arch *)((char *)header + sizeof(struct fat_header));
	n_arch = 0;
	while (n_arch < header->nfat_arch)
	{
		if (bin_size < full_size + sizeof(struct fat_arch) || \
			bin_size < arch->offset + arch->size)
		{
			errno = E_NT_TRMLF;
			return (NULL);
		}
		if (arch->cputype == CPU_TYPE_X86_64 && \
			arch->cpusubtype == CPU_SUBTYPE_X86_64_ALL)
			return (arch);
	}
	errno = E_NT_NTVLD;
	return (NULL);
}

int	parse_fat_header_32(t_binary_info *binary_info)
{
	struct	fat_header *header;
	struct	fat_arch *arch;
	size_t	offset;
	size_t	size;

	header = get_header(binary_info->map_start, binary_info->file_stat.st_size);
	if (!header)
		return (1);
	arch = get_arch(header, binary_info->file_stat.st_size);
	if (!arch)
		return (1);
	offset = arch->offset;
	size = arch->size;
	munmap(binary_info->map_start, binary_info->file_stat.st_size);
	binary_info->map_start = mmap(0, size, \
		PROT_READ, MAP_SHARED, binary_info->fd, (off_t) offset);
	return (0);
}