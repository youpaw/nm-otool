//
// Created by Darth Butterwell on 6/3/21.
//

#include "ft_printf.h"
#include "otool.h"

static t_vec *(*g_sections_data_handlers[N_BIN_TYPES][N_ARCH_TYPES]) \
	(t_vec *, t_binary_info *binary_info) = {
	{&get_sections_data_mach_o_32, &get_sections_data_mach_o_64}
};

static void	print_sects_data(t_vec *sections_data, t_binary_info *binary_info)
{
	static const char	*print_fmt[N_ARCH_TYPES] = \
		{"%08zx\t", "%016zx\t"};
	uint32_t			cnt;
	t_sect_data			sect_data;

	cnt = 0;
	while (cnt < sections_data->size)
	{
		ft_vec_get_at(&sect_data, sections_data, cnt);
		ft_printf("Contents of (%s,%s) section\n", sect_data.segname, \
			sect_data.sectname);
		print_hexdump(print_fmt[binary_info->arch], \
			binary_info->mapstart + sect_data.offset, \
				sect_data.addr, sect_data.size);
		cnt++;
	}
}

int	print_sects(t_vec *load_cmds, t_binary_info *binary_info)
{
	t_vec	*sections_data;

	sections_data = g_sections_data_handlers \
		[binary_info->type][binary_info->arch](load_cmds, binary_info);
	if (sections_data)
	{
		ft_printf("%s:\n", g_av[g_nc]);
		print_sects_data(sections_data, binary_info);
		ft_vec_del(&sections_data);
		return (0);
	}
	return (errno);
}
