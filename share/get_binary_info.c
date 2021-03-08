//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"
#include "ft_mem.h"
#include <errno.h>

t_binary_info *get_binary_info(const char *path)
{
	int				fd;
	t_binary_info	*binary_info;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		g_error_code = errno;
		return (NULL);
	}
	binary_info = ft_xmalloc(sizeof(t_binary_info));
	stat(path, &(binary_info->file_stat));
	binary_info->map_start = mmap(0, binary_info->file_stat.st_size, \
		PROT_READ, MAP_SHARED, fd, 0);
	ft_bzero(&binary_info->magic, sizeof(size_t));
	if (parse_magic(binary_info))
	{
		munmap(binary_info->map_start, binary_info->file_stat.st_size);
		free(binary_info);
		return (NULL);
	}
	binary_info->fd = fd;
	return (binary_info);
}
