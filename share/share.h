//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef SHARE_H
# define SHARE_H
# include <mach-o/loader.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include "ft_error.h"
# include "ft_vec.h"
# define N_BIN_TYPES 1
# define N_ARCH_TYPES 2
# define N_MAGIC_NUMBERS 2
# define SEGMENTS_VEC_CAPACITY 20
# define SECTIONS_VEC_CAPACITY 20

typedef enum e_bin_type{
	e_mach_o
}				t_bin_type;

typedef enum e_arch_type{
	e_32,
	e_64
}				t_arch_type;

typedef struct s_magic_map{
	enum e_arch_type	arch;
	size_t				size;
	uint32_t			magic;
}				t_magic_map;

typedef struct s_binary_info{
	int					fd;
	struct stat			file_stat;
	void				*map_start;
	enum e_bin_type		type;
	enum e_arch_type	arch;
	size_t				magic;
}				t_binary_info;

typedef struct s_check_sizes{
	size_t				cmds;
	size_t				full;
}				t_check_sizes;

int						print_nt_error(int error);

int						parse_magic(t_binary_info *binary_info);
int 					parse_fat_header(t_binary_info *binary_info);
int						parse_fat_header_32(t_binary_info *binary_info);
int						parse_fat_header_64(t_binary_info *binary_info);
t_binary_info			*get_binary_info(const char *path);
void					del_binary_info(t_binary_info **binary_info);

t_vec					*get_load_cmds_mach_o_32(void *map_start, \
	size_t bin_size);
t_vec					*get_load_cmds_mach_o_64(void *map_start, \
	size_t bin_size);
t_vec					*get_load_cmds(t_binary_info *binary_info);

t_vec					*get_sections_mach_o_32(t_vec *load_cmds);
t_vec					*get_sections_mach_o_64(t_vec *load_cmds);

void					print_hexdump(const char *fmt, const void *data, \
	size_t addr, size_t size);

# define N_NT_ERRORS 2
# define E_NT_NTVLD 107
# define E_NT_TRMLF 108
# define E_NT_LAST 109

#endif //SHARE_H
