#include "shlogic.h"

pid_t		execute_cmd(t_cmd_env *cmd_env, t_rostr cmd_path)
{
	pid_t	pid;
	t_str	*env_tab;

	pid = fork();
	if (pid == -1)
		ft_err_erno(errno, TRUE);

	if (pid == CHILD_PROCESS_PID)
	{
		// ft_printf("{blue}started %s from %d/%d\n", cmd_path, getpid(), getppid());
		dup_and_close(cmd_env->fd_io.in, STDIN_FILENO, TRUE);
		dup_and_close(cmd_env->fd_io.out, STDOUT_FILENO, TRUE);
		dup_and_close(cmd_env->fd_io.err, STDERR_FILENO, TRUE);

		dup_and_closelst(cmd_env->fd_io.other, TRUE);

		env_tab = shvars_form_key_val_tab(cmd_env->shvars->env);
		if (execve(cmd_path, cmd_env->argv, env_tab) == -1)
		{
			ft_error(TRUE, "%s: %s: %s\n",
				g_proj_name, cmd_env->argv[0], strerror(errno));
		}
	}

	return pid;
}
