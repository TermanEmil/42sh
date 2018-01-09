#include "shlogic.h"

static int	*save_this_process_fds_(const t_lst_to_dup *other_fds)
{
	int					*saved_fds;
	int					i;
	const t_to_dup		*to_dup;
	const t_lst_to_dup	*lst_to_dup;

	saved_fds = malloc(sizeof(int) * (3 + ft_lstlen(other_fds)));
	if (saved_fds == NULL)
		ft_err_mem(TRUE);

	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	saved_fds[2] = dup(STDERR_FILENO);
	if (errno != 0)
		ft_err_erno(errno, TRUE);

	lst_to_dup = other_fds;
	for (i = 3; lst_to_dup; LTONEXT(lst_to_dup), i++)
	{
		to_dup = LCONT(lst_to_dup, t_to_dup*);
		if (to_dup->default_fd >= 0)
			saved_fds[i] = dup(to_dup->default_fd);
		if (errno != 0)
			ft_err_erno(errno, TRUE);
	}
	return saved_fds;
}

static void	restore_this_process_fds_(
				const int *saved_fds,
				const t_lst_to_dup *other_fds)
{
	int					i;
	const t_to_dup		*to_dup;
	const t_lst_to_dup	*lst_to_dup;

	dup_and_close(saved_fds[0], STDIN_FILENO, TRUE);
	dup_and_close(saved_fds[1], STDOUT_FILENO, TRUE);
	dup_and_close(saved_fds[2], STDERR_FILENO, TRUE);

	lst_to_dup = other_fds;
	for (i = 3; lst_to_dup; LTONEXT(lst_to_dup), i++)
	{
		to_dup = LCONT(lst_to_dup, t_to_dup*);
		if (to_dup->default_fd >= 0)
		{
			if (dup2(saved_fds[i], to_dup->default_fd) == -1)
				ft_err_erno(errno, TRUE);
			if (close(saved_fds[i]) == -1)
				ft_err_erno(errno, TRUE);
		}
	}
}

/*
** Because the builtins must be executed on the same process as the shell,
** the current process' fd-s must be first saved.
*/

void		execute_built_in(t_cmd_env *cmd_env, t_exec_cmd_f *exec_cmd_f)
{
	int	*saved_fds;

	saved_fds = save_this_process_fds_(cmd_env->fd_io.other);

	dup_and_close(cmd_env->fd_io.in, STDIN_FILENO, FALSE);
	dup_and_close(cmd_env->fd_io.out, STDOUT_FILENO, FALSE);
	dup_and_close(cmd_env->fd_io.err, STDERR_FILENO, FALSE);
	dup_and_closelst(cmd_env->fd_io.other, FALSE);

	exec_cmd_f(cmd_env);

	restore_this_process_fds_(saved_fds, cmd_env->fd_io.other);
	free(saved_fds);
}
