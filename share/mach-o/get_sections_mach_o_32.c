//
// Created by Darth Butterwell on 5/3/21.
//

#include "nm.h"
#include "ft_mem.h"

static int	get_section(struct section *sect, t_binary_info *binary_info, \
	size_t mapoff)
{
	struct section *sect_ptr;

	sect_ptr = (struct section *)binary_info->mapstart + mapoff;
	ft_memcpy(sect->sectname, sect_ptr->sectname, SECTNAME_SIZE);
	ft_memcpy(sect->segname, sect_ptr->segname, SEGNAME_SIZE);
	if (binary_info->swap)
	{
		sect->addr = ft_swap_uint32(sect_ptr->addr);
		sect->size = ft_swap_uint32(sect_ptr->size);
		sect->offset = ft_swap_uint32(sect_ptr->offset);
	}
	else
	{
		sect->addr = sect_ptr->addr;
		sect->size = sect_ptr->size;
		sect->offset = sect_ptr->offset;
	}
}

static int	extract_sections(t_seg_cmd_32 *seg_cmd, \
	t_binary_info *binary_info, t_vec *sects)
{
	struct section	sect;
	size_t			mapoff;
	size_t			nsect;

	mapoff = seg_cmd->mapoff + sizeof(struct segment_command);
	nsect = 0;
	while (nsect < seg_cmd->segment.nsects)
	{
		get_section(&sect, binary_info, mapoff);
		if (seg_cmd->segment.fileoff + seg_cmd->segment.filesize < \
			sect.offset + sect.size)
			return (print_nt_error(E_NT_TRMLF));
		ft_vec_push(sects, &sect);
		mapoff += sizeof(struct section);
		nsect++;
	}
	return (0);
}

t_vec *get_sections_mach_o_32(t_vec *segments, t_binary_info *binary_info)
{
	t_seg_cmd_32	segment;
	size_t			cnt;
	t_vec			*sects;

	sects = ft_vec_new(SECTIONS_VEC_CAPACITY, sizeof(struct section), NULL);
	cnt = 0;
	while (cnt < segments->size)
	{
		ft_vec_get_at(&segment, segments, cnt);
		if (extract_sections(&segment, binary_info, sects))
		{
			ft_vec_del(&sects);
			break ;
		}
		cnt++;
	}
	return (sects);
}
