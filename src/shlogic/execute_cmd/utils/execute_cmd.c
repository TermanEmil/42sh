#include "shlogic.h"

static const int	g_child_porcess_ = 0;

static void	dup_and_close_(int fd, int default_fd)
{
	if (fd != default_fd)
	{
		if (dup2(fd, default_fd) == -1)
			ft_err_erno(errno, TRUE);
		close(fd);
	}
}

pid_t		execute_cmd(
				t_input_output fd_io,
				t_rostr cmd_path,
				const t_str *argv,
				t_shvars *shvars)
{
	pid_t	pid;
	t_str	*env_tab;

	pid = fork();
	if (pid == -1)
		ft_err_erno(errno, TRUE);

	if (pid == g_child_porcess_)
	{
		dup_and_close_(fd_io.in, STDIN_FILENO);
		dup_and_close_(fd_io.out, STDOUT_FILENO);

		env_tab = shvars_form_key_val_tab(shvars->env);
		if (execve(cmd_path, argv, env_tab) == -1)
		{
			ft_free_bidimens(env_tab);
			ft_error(TRUE, "%s: %s", argv[0], strerror(errno));
		}
	}

	return pid;
}
