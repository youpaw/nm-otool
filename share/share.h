//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef SHARE_H
# define SHARE_H
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>
# include "ft_error.h"
# include "ft_vec.h"
# define N_BIN_TYPES 1
# define N_ARCH_TYPES 2
# define SEGMENTS_VEC_CAPACITY 20
# define SECTIONS_VEC_CAPACITY 20
# define SEGNAME_SIZE 16
# define SECTNAME_SIZE 16

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
	char				swap;
	size_t				size;
	size_t				archoff;
	size_t				archsize;
	void				*mapstart;
	enum e_bin_type		type;
	enum e_arch_type	arch;
	size_t				magic;
}				t_binary_info;

typedef struct s_seg_cmd_32
{
	struct segment_command	segment;
	size_t					mapoff;
}				t_seg_cmd_32;

typedef struct s_seg_cmd_64
{
	struct segment_command_64	segment;
	size_t						mapoff;
}				t_seg_cmd_64;

int						print_nt_error(int error);

int						parse_magic(t_binary_info *binary_info);
int						get_header_fat(struct fat_header *fat_header, \
	t_binary_info *binary_info);
int						parse_header_fat(t_binary_info *binary_info);
int						parse_header_fat_32(t_binary_info *binary_info);
int						parse_header_fat_64(t_binary_info *binary_info);

t_binary_info			*get_binary_info(const char *path);
void					del_binary_info(t_binary_info **binary_info);

int						get_load_cmd(struct load_command *load_command, \
	t_binary_info *binary_info, size_t mapoff);
int						get_header_mach_o_32(struct mach_header *header, \
	t_binary_info *binary_info);
int						get_header_mach_o_64(struct mach_header_64 *header, \
	t_binary_info *binary_info);
t_vec					*get_segments_mach_o_32(t_binary_info *binary_info);
t_vec					*get_segments_mach_o_64(t_binary_info *binary_info);
t_vec					*get_segments(t_binary_info *binary_info);

t_vec					*get_sections_mach_o_32(t_vec *segments, \
	t_binary_info *binary_info);
t_vec					*get_sections_mach_o_64(t_vec *segments, \
	t_binary_info *binary_info);

void					print_hexdump(const char *fmt, const void *data, \
	size_t addr, size_t size);

# define N_NT_ERRORS 2
# define E_NT_NTVLD 107
# define E_NT_TRMLF 108
# define E_NT_LAST 109

#endif //SHARE_H
