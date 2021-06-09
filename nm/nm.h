//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef NM_H
# define NM_H
# include <mach-o/nlist.h>
# include "share.h"
# define DEFAULT_FILE_PATH "a.out"
# define N_SYM_MAP 3
# define SYM_NAME_SIZE 16

typedef struct s_sym_info{
	size_t		value;
	uint8_t		nsect;
	uint8_t		ntype;
	char		c;
	char		*str;
}				t_sym_info;

typedef struct s_sym_map{
	char		sect_name[SYM_NAME_SIZE];
	char		sym;
}				t_sym_map;

typedef struct s_sym_tab
{
	char		*str_tab;
	void		*tab;
}				t_sym_tab;

struct symtab_command	*get_symtab_cmd(t_vec *load_cmds);

int						print_symtab(struct symtab_command *symtab_cmd, \
	t_vec *load_cmds, t_binary_info *binary_info);

int						get_symbol_char(uint8_t type, uint8_t n_sect, \
	const char *sectname, char *c);

t_sym_info				**get_sym_info_table_mach_o_32( t_binary_info \
	*binary_info, struct symtab_command *symtab_cmd, t_vec *load_cmds);
t_sym_info				**get_sym_info_table_mach_o_64(t_binary_info \
	*binary_info, struct symtab_command *symtab_cmd, t_vec *load_cmds);

int						cmp_sym_info(const t_sym_info *l, const t_sym_info *r);

#endif //NM_H
