//
// Created by Darth Butterwell on 3/8/21.
//

#include "share.h"

static struct mach_header	*get_header(void *map_start, size_t bin_size, \
	t_check_sizes *check)
{
	struct mach_header	*header;

	check->full = sizeof(struct mach_header);
	if (bin_size < check->full)
		return (NULL);
	header = (struct mach_header *) map_start;
	check->cmds = 0;
	return (header);
}

static int	validate_load_cmds(struct load_command *lc, size_t bin_size, \
	t_check_sizes *check)
{
	struct segment_command	*seg_cmd;

	if ((bin_size < (check->full + sizeof(struct load_command))) || \
		(bin_size < (check->full + lc->cmdsize)))
		return (1);
	if (lc->cmd == LC_SEGMENT)
	{
		seg_cmd = (struct segment_command *) lc;
		if (bin_size < (seg_cmd->fileoff + seg_cmd->filesize))
			return (1);
		if (seg_cmd->cmdsize < (sizeof(struct segment_command) + \
			seg_cmd->nsects * sizeof(struct section)))
			return (1);
	}
	check->cmds += lc->cmdsize;
	check->full += lc->cmdsize;
	return (0);
}

t_vec	*get_load_cmds_mach_o_32(void *map_start, size_t bin_size)
{
	struct mach_header	*header;
	struct load_command	*ld_cmd;
	t_vec				*segments;
	size_t				n_cmds;
	t_check_sizes		check;

	header = get_header(map_start, bin_size, &check);
	if (!header)
		return (NULL);
	segments = ft_vec_new(SEGMENTS_VEC_CAPACITY, sizeof(void *), NULL);
	if (header->ncmds > 0)
		ld_cmd = (struct load_command *)((char *) header + \
			sizeof(struct mach_header));
	n_cmds = 0;
	while (n_cmds < header->ncmds)
	{
		if (validate_load_cmds(ld_cmd, bin_size, &check))
			break ;
		ft_vec_push(segments, &ld_cmd);
		ld_cmd = (struct load_command *)((char *)ld_cmd + ld_cmd->cmdsize);
		n_cmds++;
	}
	if (n_cmds < header->ncmds || check.cmds != header->sizeofcmds)
		ft_vec_del(&segments);
	return (segments);
}
