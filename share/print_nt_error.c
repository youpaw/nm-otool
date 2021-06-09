//
// Created by Darth Butterwell on 3/7/21.
//

#include "share.h"

int	print_nt_error(int error)
{
	static const char	*nt_err[N_NT_ERRORS] = {
			"The file was not recognized as a valid object file.",
			"The file is truncated or malformed object."
	};

	errno = error;
	if (errno > ELAST && errno < E_NT_LAST)
		return (ft_print_error(nt_err[errno - ELAST - 1]));
	else
		return (ft_print_error(NULL));
}
