//
// Created by Darth Butterwell on 3/8/21.
//

#include "share.h"
#include "ft_mem.h"

static void extract_segment_data(struct segment_command *seg, \
	struct segment_command *seg_ptr)
{
	seg->cmdsize = seg_ptr->cmdsize;
	seg->fileoff = seg_ptr->fileoff;
	seg->filesize = seg_ptr->filesize;
	seg->nsects = seg_ptr->nsects;
}

static void	extract_segment_data_swap(struct segment_command *seg, \
	struct segment_command *seg_ptr)
{
	seg->cmdsize = ft_swap_uint32(seg_ptr->cmdsize);
	seg->fileoff = ft_swap_uint32(seg_ptr->fileoff);
	seg->filesize = ft_swap_uint32(seg_ptr->filesize);
	seg->nsects = ft_swap_uint32(seg_ptr->nsects);
}

static int	get_segment(struct segment_command *seg, \
	t_binary_info *bin_info, size_t mapoff)
{
	struct segment_command	*seg_ptr;

	if (bin_info->archsize < sizeof(struct segment_command) + mapoff)
		return (1);
	seg_ptr = (struct segment_command *)((char *)bin_info->mapstart + mapoff);
	if (bin_info->swap)
		extract_segment_data_swap(seg, seg_ptr);
	else
		extract_segment_data(seg, seg_ptr);
	if ((bin_info->archoff + bin_info->archsize) < \
		(seg->fileoff + seg->filesize))
		return (1);
	if (seg->cmdsize < (sizeof(struct segment_command) + \
		seg->nsects * sizeof(struct section)))
		return (1);
	return (0);
}

static t_vec	*extract_segments(struct mach_header *header, \
	t_binary_info *bin_info)
{
	struct load_command		ld_cmd;
	t_seg_cmd_32			seg_cmd;
	t_vec					*segments;
	size_t					n_cmds;
	size_t					mapoff;

	segments = ft_vec_new(SEGMENTS_VEC_CAPACITY, sizeof(t_seg_cmd_32), NULL);
	mapoff = sizeof(struct mach_header);
	n_cmds = -1;
	while (++n_cmds < header->ncmds)
	{
		if (get_load_cmd(&ld_cmd, bin_info, mapoff))
			break ;
		if (ld_cmd.cmd == LC_SEGMENT)
		{
			if (get_segment(&seg_cmd.segment, bin_info, mapoff))
				break ;
			ft_vec_push(segments, &seg_cmd);
		}
		mapoff += ld_cmd.cmdsize;
	}
	if (n_cmds < header->ncmds || mapoff != header->sizeofcmds)
		ft_vec_del(&segments);
	return (segments);
}

t_vec	*get_segments_mach_o_32(t_binary_info *binary_info)
{
	struct mach_header	header;

	if (get_header_mach_o_32(&header, binary_info))
		return (NULL);
	return (extract_segments(&header, binary_info));
}
