//
// Created by Darth Butterwell on 6/3/21.
//

#include "otool.h"
#include "ft_str.h"

static t_vec	*get_sections_data(t_vec *sects, const char *segname, \
	const char *sectname)
{
	t_sect_data		sect_data;
	t_section_64	*sect;
	size_t			cnt;
	t_vec			*sects_data;

	sects_data = ft_vec_new(SECTIONS_VEC_CAPACITY, sizeof(t_sect_data), NULL);
	cnt = 0;
	while (cnt < sects->size)
	{
		ft_vec_get_at(&sect, sects, cnt);
		if (!ft_strcmp(segname, sect->segname) && \
			!ft_strcmp(sectname, sect->sectname))
		{
			sect_data.sectname = sect->sectname;
			sect_data.segname = sect->segname;
			sect_data.addr = sect->addr;
			sect_data.size = sect->size;
			sect_data.offset = sect->offset;
			ft_vec_push(sects_data, &sect_data);
		}
		cnt++;
	}
	return (sects_data);
}

t_vec *get_sections_data_mach_o_64(t_vec *load_cmds)
{
	t_vec		*sects;
	t_vec		*sects_data;

	sects = get_sections_mach_o_64(load_cmds);
	if (sects)
	{
		sects_data = get_sections_data(sects, SEG_TEXT, SECT_TEXT);
		ft_vec_del(&sects);
		return (sects_data);
	}
	return (NULL);
}