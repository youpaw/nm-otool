//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"

t_vec *get_load_cmds(t_binary_info *binary_info)
{
	static t_vec	*(*segment_parser_handlers[N_BIN_TYPES][N_ARCH_TYPES]) \
		(void *, size_t) = {
			{&get_load_cmds_mach_o_32, &get_load_cmds_mach_o_64}
	};
	t_vec *segments;

	segments = segment_parser_handlers[binary_info->type][binary_info->arch] \
		(binary_info->map_start, binary_info->file_stat.st_size);
	if (!segments)
		print_nt_error(E_NT_TRMLF);
	return (segments);
}