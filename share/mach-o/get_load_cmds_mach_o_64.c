//
// Created by Darth Butterwell on 3/8/21.
//

#include "share.h"

static t_mach_header_64	*get_header(void *map_start, size_t bin_size, \
	t_check_sizes *check)
{
	t_mach_header_64 *header;
	check->full = sizeof(t_mach_header_64);
	if (bin_size < check->full)
		return (NULL);
	header = (t_mach_header_64 *)map_start;
	check->cmds = 0;
	return (header);
}

static int				validate_load_cmds(t_load_cmd *lc, size_t bin_size, \
	t_check_sizes *check, size_t n)
{
	t_segment_cmd_64 *seg_cmd;

	(void) n;
	if ((bin_size < (check->full + sizeof(t_load_cmd))) || \
		(bin_size < (check->full + lc->cmdsize)))
		return (1);
	if (lc->cmd == LC_SEGMENT_64)
	{
		seg_cmd = (t_segment_cmd_64 *) lc;
		if (bin_size < (seg_cmd->fileoff + seg_cmd->filesize))
			return (1);
		if (seg_cmd->cmdsize < (sizeof(t_segment_cmd_64) + \
			seg_cmd->nsects * sizeof(t_section_64)))
			return (1);
	}
	check->cmds += lc->cmdsize;
	check->full += lc->cmdsize;
	return (0);
}

t_vec *get_load_cmds_mach_o_64(void *map_start, size_t bin_size)
{
	t_mach_header_64	*header;
	t_load_cmd			*load_cmd;
	t_vec				*segments;
	size_t				n_cmds;
	t_check_sizes		check;

	header = get_header(map_start, bin_size, &check);
	if (!header)
		return (NULL);
	segments = ft_vec_new(SEGMENTS_VEC_CAPACITY, sizeof(void *),NULL);
	if (header->ncmds > 0)
		load_cmd = (t_load_cmd *) ((char *)header + sizeof(t_mach_header_64));
	n_cmds = 0;
	while (n_cmds < header->ncmds)
	{
		if (validate_load_cmds(load_cmd, bin_size, &check, n_cmds))
			break;
		ft_vec_push(segments, &load_cmd);
		load_cmd = (t_load_cmd *)((char *)load_cmd + load_cmd->cmdsize);
		n_cmds++;
	}
	if (n_cmds < header->ncmds || check.cmds != header->sizeofcmds)
		ft_vec_del(&segments);
	return (segments);
}
