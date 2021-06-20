//
// Created by Darth Butterwell on 6/3/21.
//

#include "otool.h"
#include "ft_str.h"
#include "ft_mem.h"

static void	get_sect_data(t_sect_data *sect_data, struct section *section, \
	char swap)
{
	ft_memcpy(sect_data->sectname, section->sectname, SECTNAME_SIZE);
	ft_memcpy(sect_data->segname, section->segname, SEGNAME_SIZE);
	if (swap)
	{
		sect_data->addr = ft_swap_uint32(section->addr);
		sect_data->size = ft_swap_uint32(section->size);
		sect_data->offset = ft_swap_uint32(section->offset);
	}
	else
	{
		sect_data->addr = section->addr;
		sect_data->size = section->size;
		sect_data->offset = section->offset;
	}
}

static t_vec	*get_sections_data(t_vec *sects, const char *segname, \
	const char *sectname, char swap)
{
	t_sect_data		sect_data;
	struct section	sect;
	size_t			cnt;
	t_vec			*sects_data;

	sects_data = ft_vec_new(SECTIONS_VEC_CAPACITY, sizeof(t_sect_data), NULL);
	cnt = 0;
	while (cnt < sects->size)
	{
		ft_vec_get_at(&sect, sects, cnt);
		if (!ft_strcmp(segname, sect.segname) && \
			!ft_strcmp(sectname, sect.sectname))
		{
			get_sect_data(&sect_data, &sect, swap);
			ft_vec_push(sects_data, &sect_data);
		}
		cnt++;
	}
	return (sects_data);
}

t_vec	*get_sections_data_mach_o_32(t_vec *load_cmds, \
	t_binary_info *binary_info)
{
	t_vec	*sects;
	t_vec	*sects_data;

	sects = get_sections_mach_o_32(load_cmds, binary_info);
	if (sects)
	{
		sects_data = get_sections_data(sects, SEG_TEXT, SECT_TEXT, \
			binary_info->swap);
		ft_vec_del(&sects);
		return (sects_data);
	}
	return (NULL);
}
