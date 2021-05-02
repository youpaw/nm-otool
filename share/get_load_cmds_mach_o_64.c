//
// Created by Darth Butterwell on 3/8/21.
//

#include "share.h"

static t_mach_header_64	*get_header(void *map_start, size_t bin_size, \
	t_load_cmd **load_cmd, t_vec **segments, t_check_sizes *check)
{
	t_mach_header_64 *header;
	check->full = sizeof(t_mach_header_64);
	if (bin_size < check->full)
		return (NULL);
	header = (t_mach_header_64 *)map_start;
	*segments = ft_vec_new(SEGMENTS_VEC_CAPACITY, sizeof(void *),NULL);
	if (header->ncmds > 0)
		*load_cmd = (t_load_cmd *) ((char *)header + sizeof(t_mach_header_64));
	check->cmds = 0;
	return (header);
}

t_vec					*get_load_cmds_mach_o_64(void *map_start, \
	size_t bin_size, char cmd)
{
	t_mach_header_64	*header;
	t_load_cmd			*load_cmd;
	t_vec				*segments;
	size_t				n_cmds;
	t_check_sizes		check;

	if (!(header = \
		get_header(map_start, bin_size, &load_cmd, &segments, &check)))
		return (NULL);
	n_cmds = 0;
	while (n_cmds < header->ncmds)
	{
		if (validate_load_cmds(load_cmd, bin_size, &check))
			break;
		if (cmd < 0 || cmd == load_cmd->cmd)
			ft_vec_push(segments, &load_cmd);
		load_cmd = (t_load_cmd *)((char *)load_cmd + load_cmd->cmdsize);
		n_cmds++;
	}
	if (n_cmds < header->ncmds || check.cmds != header->sizeofcmds)
		ft_vec_del(&segments);
	return (segments);
}
