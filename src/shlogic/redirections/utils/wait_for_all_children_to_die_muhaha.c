#include "shell_redirs_.h"
#include <sys/wait.h>
#include <sys/types.h>
       #include <sys/wait.h>


/*
** It's ok if it didn't wait for anything.
*/

void	wait_for_all_children_to_die_muhaha()
{
	while (waitpid(-1, NULL, 0) > 0 && !g_shinput->signaled_sigint);

	if (errno)
	{
		if (errno == ECHILD || errno == EINTR)
			errno = 0;
		else
			ft_err_erno(errno, TRUE);
	}
}
