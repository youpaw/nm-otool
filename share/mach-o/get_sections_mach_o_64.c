//
// Created by Darth Butterwell on 5/3/21.
//

#include "nm.h"

static int	get_sects(struct segment_command_64 *seg, t_vec *sects)
{
	size_t				cnt;
	struct section_64	*sect;

	sect = (struct section_64 *)((char *)seg + \
		sizeof(struct segment_command_64));
	cnt = 0;
	while (cnt < seg->nsects)
	{
		if (seg->fileoff + seg->filesize < sect->offset + sect->size)
			return (print_nt_error(E_NT_TRMLF));
		ft_vec_push(sects, &sect);
		sect = (struct section_64 *)((char *)sect + sizeof(struct section_64));
		cnt++;
	}
	return (0);
}

t_vec	*get_sections_mach_o_64(t_vec *load_cmds)
{
	struct load_command	*lc;
	size_t				cnt;
	t_vec				*sects;

	sects = ft_vec_new(SECTIONS_VEC_CAPACITY, sizeof(void *), NULL);
	cnt = 0;
	while (cnt < load_cmds->size)
	{
		ft_vec_get_at(&lc, load_cmds, cnt);
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (get_sects((struct segment_command_64 *)lc, sects))
			{
				ft_vec_del(&sects);
				break ;
			}
		}
		cnt++;
	}
	return (sects);
}
