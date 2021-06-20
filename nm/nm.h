//
// Created by Darth Butterwell on 3/7/21.
//

#ifndef NM_H
# define NM_H
# include <mach-o/nlist.h>
# include "share.h"
# define DEFAULT_FILE_PATH "a.out"
# define NLISTS_VEC_CAPACITY 20
# define N_SYM_MAP 3

typedef struct s_sym_info{
	size_t		value;
	uint8_t		nsect;
	uint8_t		ntype;
	char		c;
	char		*str;
}				t_sym_info;

typedef struct s_sym_map{
	char		sectname[SECTNAME_SIZE];
	char		sym;
}				t_sym_map;

int						print_symtab(struct symtab_command *symtab_cmd, \
	t_vec *load_cmds, t_binary_info *binary_info);

int						get_symbol_char(uint8_t type, uint8_t n_sect, \
	const char *sectname, char *c);

t_vec					*get_nlists_mach_o_32(struct symtab_command \
	*symtab_cmd, t_binary_info *binary_info);
t_vec					*get_nlists_mach_o_64(struct symtab_command \
	*symtab_cmd, t_binary_info *binary_info);

int						get_symtab_cmd(struct symtab_command *symtab, \
	t_binary_info *binary_info);
int						get_symtab_cmd_mach_o_32(struct symtab_command \
	*symtab, t_binary_info *binary_info);
int						get_symtab_cmd_mach_o_64(struct symtab_command \
	*symtab, t_binary_info *binary_info);
t_sym_info				**get_sym_info_table_mach_o_32( t_binary_info \
	*binary_info, struct symtab_command *symtab_cmd, t_vec *load_cmds);
t_sym_info				**get_sym_info_table_mach_o_64(t_binary_info \
	*binary_info, struct symtab_command *symtab_cmd, t_vec *load_cmds);

int						cmp_sym_info(const t_sym_info *l, const t_sym_info *r);

#endif //NM_H
