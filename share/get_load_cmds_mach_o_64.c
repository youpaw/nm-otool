//
// Created by Darth Butterwell on 3/8/21.
//

#include "share.h"

t_vec			*get_load_cmds_mach_o_64(void *map_start, char cmd)
{
	t_load_cmd	*load_cmd;
	t_vec		*segments;
	size_t		n_cmds;

	segments = ft_vec_new(SEGMENTS_VEC_CAPACITY, sizeof(void *),NULL);
	t_mach_header_64 *header = (t_mach_header_64 *)map_start;
	if (header->ncmds > 0)
		load_cmd = (t_load_cmd *) ((char *)header + sizeof(t_mach_header_64));
	n_cmds = 0;
	while (n_cmds < header->ncmds)
	{
		if (cmd < 0 || cmd == load_cmd->cmd)
			ft_vec_push(segments, &load_cmd);
		load_cmd = (t_load_cmd *)((char *)load_cmd + load_cmd->cmdsize);
		n_cmds++;
	}
	return (segments);
}
