//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef SHARE_H
#define SHARE_H

#include <mach-o/loader.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "ft_vec.h"
#define N_BIN_TYPES 1
#define N_ARCH_TYPES 2
#define N_MAGIC_NUMBERS 2
#define SEGMENTS_VEC_CAPACITY 20

extern int g_error_code;



typedef enum	e_bin_type{
	e_mach_o
}				t_bin_type;

typedef enum	e_arch_type{
	e_32,
	e_64
}				t_arch_type;

typedef struct	s_magic_map{
	enum e_arch_type	arch;
	size_t				size;
	uint32_t			magic[N_MAGIC_NUMBERS];
}				t_magic_map;

typedef struct s_binary_info{
	int					fd;
	struct stat 		file_stat;
	void 				*map_start;
	enum e_bin_type		type;
	enum e_arch_type	arch;
	size_t				magic;
}				t_binary_info;

typedef struct stat t_stat;
typedef struct mach_header t_mach_header_32;
typedef struct mach_header_64 t_mach_header_64;
typedef struct load_command t_load_cmd;
typedef struct segment_command t_segment_cmd_32;
typedef struct segment_command_64 t_segment_cmd_64;
typedef struct section t_section_32;
typedef struct section_64 t_section_64;

void			print_error(const char *name, const char *arg);
int				parse_magic(t_binary_info *binary_info);
t_binary_info	*get_binary_info(const char *path);
void 			del_binary_info(t_binary_info **binary_info);

t_vec			*get_load_cmds_mach_o_32(void *map_start, char cmd);
t_vec			*get_load_cmds_mach_o_64(void *map_start, char cmd);
t_vec			*get_load_cmds(t_binary_info *binary_info, char cmd);

# define MAGIC_ERROR (128 + 1)

#endif //SHARE_H
