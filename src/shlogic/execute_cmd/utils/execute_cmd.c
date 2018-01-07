#include "shlogic.h"

static void	dup_and_close_(int fd, int default_fd, t_bool close_it)
{
	if (fd != default_fd)
	{
		if (dup2(fd, default_fd) == -1)
			ft_err_erno(errno, TRUE);
		if (close_it &&
			fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		{
			close(fd);
			errno = 0;
		}
	}
}

static void	dup_and_close_lst_(const t_lst_to_dup *lst_to_dup, t_bool close_it)
{
	const t_to_dup	*to_dup;

	for (; lst_to_dup; LTONEXT(lst_to_dup))
	{
		to_dup = LCONT(lst_to_dup, t_to_dup*);
		if (to_dup->to_close)
		{
			close(to_dup->fd);
			errno = 0;
		}
		else
			dup_and_close_(to_dup->fd, to_dup->default_fd, close_it);
	}
}

pid_t		execute_cmd(t_cmd_env *cmd_env, t_rostr cmd_path)
{
	pid_t	pid;
	t_str	*env_tab;

	pid = fork();
	if (pid == -1)
		ft_err_erno(errno, TRUE);

	if (pid == CHILD_PROCESS_PID)
	{
		dup_and_close_(cmd_env->fd_io.in, STDIN_FILENO, TRUE);
		dup_and_close_(cmd_env->fd_io.out, STDOUT_FILENO, TRUE);
		dup_and_close_(cmd_env->fd_io.err, STDERR_FILENO, TRUE);

		dup_and_close_lst_(cmd_env->fd_io.other, TRUE);

		env_tab = shvars_form_key_val_tab(cmd_env->shvars->env);
		if (execve(cmd_path, cmd_env->argv, env_tab) == -1)
		{
			ft_error(TRUE, "%s: %s: %s\n",
				g_proj_name, cmd_env->argv[0], strerror(errno));
		}
	}

	return pid;
}

void		execute_built_in(t_cmd_env *cmd_env, t_exec_cmd_f *exec_cmd_f)
{
	int					*saved_fd;
	const t_lst_to_dup	*lst_to_dup;
	int					i;
	int	fd;

	saved_fd = malloc(sizeof(int) * (3 + ft_lstlen(cmd_env->fd_io.other)));
	if (saved_fd == NULL)
		ft_err_mem(TRUE);

	saved_fd[0] = dup(STDIN_FILENO);
	saved_fd[1] = dup(STDOUT_FILENO);
	saved_fd[2] = dup(STDERR_FILENO);

	for (lst_to_dup = cmd_env->fd_io.other, i = 3; lst_to_dup; LTONEXT(lst_to_dup), i++)
		saved_fd[i] = dup(LCONT(lst_to_dup, t_to_dup*)->default_fd);

	dup_and_close_(cmd_env->fd_io.in, STDIN_FILENO, FALSE);
	dup_and_close_(cmd_env->fd_io.out, STDOUT_FILENO, FALSE);
	dup_and_close_(cmd_env->fd_io.err, STDERR_FILENO, FALSE);
	dup_and_close_lst_(cmd_env->fd_io.other, FALSE);

	exec_cmd_f(cmd_env);

	dup_and_close_(saved_fd[0], STDIN_FILENO, TRUE);
	dup_and_close_(saved_fd[1], STDOUT_FILENO, TRUE);
	dup_and_close_(saved_fd[2], STDERR_FILENO, TRUE);

	for (lst_to_dup = cmd_env->fd_io.other, i = 3; lst_to_dup; LTONEXT(lst_to_dup), i++)
	{
		dup2(saved_fd[i], LCONT(lst_to_dup, t_to_dup*)->default_fd);
		close(saved_fd[i]);
	}

	free(saved_fd);
}