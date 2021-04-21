//
// Created by Darth Butterwell on 4/21/21.
//

#include "nm.h"
#include "ft_str.h"

int 		cmp_sym_info(const t_sym_info *l, const t_sym_info *r)
{
	return (ft_strcmp(l->str, r->str));
}
