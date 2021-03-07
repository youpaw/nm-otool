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
#define N_MAGICK_NUMBERS 2

extern int g_error_code;



typedef enum	e_bin_type{
	e_mach_o
}				t_bin_type;

typedef enum	e_arch_type{
	e_32,
	e_64
}				t_arch_type;

typedef struct	s_magick_map{
	enum e_arch_type	arch;
	uint32_t			magick[N_MAGICK_NUMBERS]
}				t_magick_map;

typedef struct s_binary_info{
	int			fd;
	struct stat file_stat;
	void 		*map_start;
	enum e_bin_type type;
	int			arch;
}				t_binary_info;

typedef struct stat t_stat;
typedef struct mach_header_64 t_mach_header_64;
typedef struct load_command t_load_cmd;
typedef struct segment_command_64 t_segment_cmd_64;
typedef struct section_64 t_section_64;

void			print_error(const char *name, const char *arg);
int				parse_magick(t_binary_info *binary_info);
t_binary_info	*get_binary_info(const char *path);
void 			del_binary_info(t_binary_info **binary_info);

t_vec			*get_segments(void *map_start, char type);

#endif //SHARE_H
