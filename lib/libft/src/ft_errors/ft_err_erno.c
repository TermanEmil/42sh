#include "libft.h"
#include "ft_errors.h"
#include <string.h>

void	ft_err_erno(int errno_val, t_bool exit_program)
{
	t_str	error;

	error = strerror(errno_val);
	if (error == NULL)
		ft_proj_err("strerror failed", exit_program);
	else
		ft_proj_err(error, exit_program);
}