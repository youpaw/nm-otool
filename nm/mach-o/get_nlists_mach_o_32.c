//
// Created by Darth Butterwell on 6/20/21.
//

#include "nm.h"
#include "ft_mem.h"

static void	get_nlist(struct nlist *nlist, size_t mapoff, \
	t_binary_info *bin_info)
{
	struct nlist	*nl_ptr;

	nl_ptr = (struct nlist *)((char *)bin_info->mapstart + mapoff);
	nlist->n_type = nl_ptr->n_type;
	nlist->n_sect = nl_ptr->n_sect;
	if (bin_info->swap)
	{
		nlist->n_un.n_strx = ft_swap_uint32(nl_ptr->n_un.n_strx);
		nlist->n_desc = ft_swap_int16(nl_ptr->n_desc);
		nlist->n_value = ft_swap_uint32(nl_ptr->n_value);
	}
	else
	{
		nlist->n_un.n_strx = nl_ptr->n_un.n_strx;
		nlist->n_desc = nl_ptr->n_desc;
		nlist->n_value = nl_ptr->n_value;
	}
}

t_vec	*get_nlists_mach_o_32(struct symtab_command *symtab_cmd, \
	t_binary_info *binary_info)
{
	struct nlist	nlist;
	size_t			mapoff;
	t_vec			*nlists;
	size_t			cnt;

	nlists = NULL;
	if ((binary_info->archsize + binary_info->archoff) < \
		(symtab_cmd->symoff + (symtab_cmd->nsyms * sizeof(struct nlist))))
		print_nt_error(E_NT_TRMLF);
	else
	{
		mapoff = symtab_cmd->symoff;
		nlists = ft_vec_new(NLISTS_VEC_CAPACITY, sizeof(struct nlist), NULL);
		cnt = 0;
		while (cnt < symtab_cmd->nsyms)
		{
			get_nlist(&nlist, mapoff, binary_info);
			ft_vec_push(nlists, &nlist);
			mapoff += sizeof(struct nlist);
			cnt++;
		}
	}
	return (nlists);
}
