//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"

const char *g_nt_err[N_NT_ERRORS] = {
		"The file was not recognized as a valid object file.",
		"The file is truncated or malformed object."
};

int print_nt_error(int error)
{
	errno = error;
	if (errno > ELAST && errno < E_NT_LAST)
		return (ft_print_error(g_nt_err[errno - ELAST - 1]));
	else
		return (ft_print_error(NULL));
}
