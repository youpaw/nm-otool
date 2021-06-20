//
// Created by Darth Butterwell on 6/3/21.
//

#ifndef OTOOL_H
# define OTOOL_H
# include "share.h"

typedef struct s_sect_data{
	char		sectname[SECTNAME_SIZE];
	char		segname[SEGNAME_SIZE];
	size_t		size;
	size_t		addr;
	size_t		offset;
}				t_sect_data;

int				print_sects(t_vec *load_cmds, t_binary_info *binary_info);

t_vec			*get_sections_data_mach_o_32(t_vec *load_cmds, \
	t_binary_info *binary_info);
t_vec			*get_sections_data_mach_o_64(t_vec *load_cmds, \
	t_binary_info *binary_info);

#endif //OTOOL_H
