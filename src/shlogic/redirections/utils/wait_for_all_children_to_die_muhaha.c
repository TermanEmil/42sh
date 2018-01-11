#include "shell_redirs_.h"
#include <sys/wait.h>
#include <sys/types.h>
       #include <sys/wait.h>


/*
** It's ok if it didn't wait for anything.
*/

void	wait_for_all_children_to_die_muhaha()
{
	pid_t	pid;

	// ft_printf("\tstarted waiting\n");
	while ((pid = waitpid(-1, NULL, 0)) > 0 && !g_shinput->signaled_sigint)
	{
		// ft_printf("{red}waited for %d\n", pid);
	}
	// ft_printf("\tended waiting\n");

	if (errno)
	{
		if (errno == ECHILD || errno == EINTR)
			errno = 0;
		else
			ft_err_erno(errno, TRUE);
	}
}
