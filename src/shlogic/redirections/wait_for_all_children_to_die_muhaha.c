#include "shell_redirs_.h"
#include <sys/wait.h>

/*
** It's ok if it didn't wait for anything.
*/

void	wait_for_all_children_to_die_muhaha()
{	
	while (wait(NULL) > 0);

	if (errno == ECHILD)
		errno = 0;
	else
		ft_err_erno(errno, TRUE);
}
