//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"
#include "ft_mem.h"

static t_binary_info	*init_binary_info(const char *path)
{
	int				fd;
	t_binary_info	*binary_info;
	struct stat		bin_stat;

	fd = open(path, O_RDONLY);
	if (fd < 0 || stat(path, &bin_stat))
	{
		print_nt_error(errno);
		return (NULL);
	}
	binary_info = ft_xmalloc(sizeof(t_binary_info));
	binary_info->size = bin_stat.st_size;
	binary_info->mapstart = mmap(0, binary_info->size, PROT_READ, MAP_SHARED, \
		fd, 0);
	ft_bzero(&binary_info->magic, sizeof(size_t));
	binary_info->fd = fd;
	binary_info->swap = 0;
	binary_info->archoff = 0;
	binary_info->archsize = bin_stat.st_size;
	return (binary_info);
}

t_binary_info	*get_binary_info(const char *path)
{
	t_binary_info	*binary_info;

	binary_info = init_binary_info(path);
	if (!binary_info)
		return (NULL);
	if (parse_magic(binary_info) && parse_header_fat(binary_info))
	{
		del_binary_info(&binary_info);
		print_nt_error(errno);
		return (NULL);
	}
	return (binary_info);
}
