//
// Created by Darth Butterwell on 5/3/21.
//

#include "nm.h"

static int get_sects(t_segment_cmd_64 *seg, t_vec *sects)
{
	size_t			cnt;
	t_section_64	*sect;

	sect = (t_section_64 *) ((char *) seg + sizeof(t_segment_cmd_64));
	cnt = 0;
	while (cnt < seg->nsects)
	{
		if (seg->cmdsize < sect->size)
		{
			return (1);
		}
		ft_vec_push(sects, &sect);
		sect = (t_section_64 *) ((char *) sect + sizeof(t_section_64));
		cnt++;
	}
	return (0);
}

t_vec		*get_sections_mach_o_64(t_vec *load_cmds)
{
	t_load_cmd		*lc;
	size_t			cnt;
	t_vec			*sects;

	sects = ft_vec_new(SECTIONS_VEC_CAPACITY, sizeof(void *), NULL);
	cnt = 0;
	while (cnt < load_cmds->size)
	{
		ft_vec_get_at(&lc, load_cmds, cnt);
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (get_sects((t_segment_cmd_64 *) lc, sects))
			{
				ft_vec_del(&sects);
				break;
			}
		}
		cnt++;
	}
	return (sects);
}