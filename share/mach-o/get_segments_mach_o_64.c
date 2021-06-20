//
// Created by Darth Butterwell on 3/8/21.
//

#include "share.h"
#include "ft_mem.h"

static void	extract_segment_data(struct segment_command_64 *seg, \
	struct segment_command_64 *seg_ptr)
{
	seg->cmdsize = seg_ptr->cmdsize;
	seg->fileoff = seg_ptr->fileoff;
	seg->filesize = seg_ptr->filesize;
	seg->nsects = seg_ptr->nsects;
}

static void	extract_segment_data_swap(struct segment_command_64 *seg, \
	struct segment_command_64 *seg_ptr)
{
	seg->cmdsize = ft_swap_uint32(seg_ptr->cmdsize);
	seg->fileoff = ft_swap_uint32(seg_ptr->fileoff);
	seg->filesize = ft_swap_uint32(seg_ptr->filesize);
	seg->nsects = ft_swap_uint32(seg_ptr->nsects);
}

static int	get_segment(struct segment_command_64 *seg, \
	t_binary_info *bin_info, size_t mapoff)
{
	struct segment_command_64	*seg_ptr;

	if (bin_info->archsize < sizeof(struct segment_command_64) + mapoff)
		return (1);
	seg_ptr = (struct segment_command_64 *) \
		((char *)bin_info->mapstart + mapoff);
	if (bin_info->swap)
		extract_segment_data_swap(seg, seg_ptr);
	else
		extract_segment_data(seg, seg_ptr);
	if ((bin_info->archoff + bin_info->archsize) < \
		(seg->fileoff + seg->filesize))
		return (1);
	if (seg->cmdsize < (sizeof(struct segment_command_64) + \
		seg->nsects * sizeof(struct section_64)))
		return (1);
	return (0);
}

static t_vec	*extract_segments(uint32_t ncmds, uint32_t sizeofcmds, \
	t_binary_info *bin_info)
{
	struct load_command		ld_cmd;
	t_seg_cmd_64			seg_cmd;
	t_vec					*segments;
	size_t					cnt;
	size_t					mapoff;

	segments = ft_vec_new(SEGMENTS_VEC_CAPACITY, sizeof(t_seg_cmd_64), NULL);
	mapoff = sizeof(struct mach_header_64);
	cnt = -1;
	while (++cnt < ncmds)
	{
		if (get_load_cmd(&ld_cmd, bin_info, mapoff))
			break ;
		if (ld_cmd.cmd == LC_SEGMENT_64)
		{
			if (get_segment(&seg_cmd.segment, bin_info, mapoff))
				break ;
			seg_cmd.mapoff = mapoff;
			ft_vec_push(segments, &seg_cmd);
		}
		mapoff += ld_cmd.cmdsize;
	}
	if (cnt < ncmds || (mapoff - sizeof(struct mach_header_64)) != sizeofcmds)
		ft_vec_del(&segments);
	return (segments);
}

t_vec	*get_segments_mach_o_64(t_binary_info *binary_info)
{
	struct mach_header_64	header;

	if (get_header_mach_o_64(&header, binary_info))
		return (NULL);
	return (extract_segments(header.ncmds, header.sizeofcmds, binary_info));
}
