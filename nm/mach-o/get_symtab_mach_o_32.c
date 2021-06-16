//
// Created by Darth Butterwell on 3/8/21.
//

#include "nm.h"
#include "ft_mem.h"

static int get_symtab(struct symtab_command *symtab, \
	t_binary_info *bin_info, size_t mapoff)
{
	struct symtab_command	*symtab_ptr;

	if (bin_info->archsize < sizeof(struct symtab_command) + mapoff)
		return (1);
	symtab_ptr = (struct symtab_command *)bin_info->mapstart + mapoff;
	if (bin_info->swap)
	{
		symtab->symoff = ft_swap_uint32(symtab_ptr->symoff);
		symtab->nsyms = ft_swap_uint32(symtab_ptr->nsyms);
		symtab->stroff = ft_swap_uint32(symtab_ptr->stroff);
		symtab->strsize = ft_swap_uint32(symtab_ptr->strsize);
	}
	else
	{
		symtab->symoff = symtab_ptr->symoff;
		symtab->nsyms = symtab_ptr->nsyms;
		symtab->stroff = symtab_ptr->stroff;
		symtab->strsize = symtab_ptr->strsize;
	}
	return (0);
}

int get_symtab_cmd_mach_o_32(struct symtab_command *symtab, \
	t_binary_info *binary_info)
{
	struct mach_header	header;
	struct load_command	load_cmd;
	size_t				mapoff;
	size_t				ncmds;

	if (get_header_mach_o_32(&header, binary_info))
		return (1);
	mapoff = sizeof(struct mach_header);
	ncmds = 0;
	while (ncmds < header.ncmds)
	{
		if (get_load_cmd(&load_cmd, binary_info, mapoff))
			break ;
		if (load_cmd.cmd == LC_SYMTAB)
		{
			if (!get_symtab(symtab, binary_info, mapoff))
				return (0);
			break ;
		}
		mapoff += load_cmd.cmdsize;
		ncmds++;
	}
	if (ncmds < header.ncmds)
		errno = E_NT_TRMLF;
	return (1);
}
