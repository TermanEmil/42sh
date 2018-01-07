#include "shell_redirs_.h"

/*
** Process the case of closing an fd, e.g.: 2>&-
*/

void		process_guillemet_close_fd(
				t_cmd_env *cmd_env,
				t_redir_env *redir_env)
{
	t_to_dup	to_dup;

	if (redir_env->left_fd == -1)
	{
		if (ft_strequ(redir_env->redir_type, "<"))
			to_dup.fd = STDIN_FILENO;
		else
			to_dup.fd = STDOUT_FILENO;
	}
	else
		to_dup.fd = redir_env->left_fd;

	to_dup.default_fd = -1;
	to_dup.to_close = TRUE;
	ft_lstadd(&cmd_env->fd_io.other, ft_lstnew(&to_dup, sizeof(to_dup)));
}
