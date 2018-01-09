#include "shell_redirs_.h"

/*
** Allocate an integer table initializing each entry with -1, so that I can
** check if it's not -1, then I can close the fd.
*/

int		*new_fd_tab_for_piping(int size)
{
	int		*fd;
	int		i;

	if ((fd = malloc(sizeof(int) * size)) == NULL)
		ft_err_mem(TRUE);
	for (i = 0; i < size; i++)
		fd[i] = -1;
	return fd;
}
