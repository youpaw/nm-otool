//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"

t_vec *(*g_segment_parser_handlers[N_BIN_TYPES][N_ARCH_TYPES]) \
	(t_binary_info *) = {
		{&get_segments_mach_o_32, &get_segments_mach_o_64}
};

t_vec	*get_segments(t_binary_info *binary_info)
{
	t_vec	*segments;

	segments = g_segment_parser_handlers[binary_info->type][binary_info->arch] \
		(binary_info);
	if (!segments)
		print_nt_error(E_NT_TRMLF);
	return (segments);
}
