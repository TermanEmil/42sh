#include "shinput.h"
#include "shlogic.h"
#include "shell42.h"
#include "regex_tools.h"
#include <sys/wait.h>
#include "shell_redirs_.h"

t_bool	argv_represents_a_subshell(const t_str *argv)
{
	return argv[0] != NULL && argv[1] == NULL &&
		regex_mini_match("^\\(.*\\)", argv[0]);
}

pid_t	process_argv(t_pipe_env *pipe_env, t_cmd_env *cmd_env)
{
	t_str			cmd_path;
	t_exec_cmd_f	*exec_cmd_f;
	pid_t			ret;

	if (cmd_env->argv[0] == NULL)
		return 0;
	g_shdata.running_a_process = TRUE;
	if (argv_represents_a_subshell(cmd_env->argv))
	{
		pid_t	pid;

		if ((pid = fork()) == -1)
			ft_err_erno(errno, TRUE);

		if (pid == CHILD_PROCESS_PID)
		{

			dup_and_close(cmd_env->fd_io.in, STDIN_FILENO, FALSE);
			dup_and_close(cmd_env->fd_io.out, STDOUT_FILENO, FALSE);
			dup_and_close(cmd_env->fd_io.err, STDERR_FILENO, FALSE);
			dup_and_closelst(cmd_env->fd_io.other, FALSE);

			t_str		raw_in;
			t_sub_sh	sub_shell;

			raw_in = ft_strnew(ft_strlen(cmd_env->argv[0]) + 1);
			ft_strcpy(raw_in, ft_strchr(cmd_env->argv[0], '(') + 1);

			if (ft_strlen(raw_in) <= 1)
				ft_error(TRUE, "syntax error near unexpected token `)'");

			raw_in[ft_strlen(raw_in) - 1] = '\n';
			g_shdata.is_term = FALSE;
			
			events_remove_with_key(g_events, "at_exit_restore_term");

			sub_shell.raw_cmd = raw_in;
			sub_shell.fd_io = cmd_env->fd_io;

			g_shdata.sub_sh = ft_memdup(&sub_shell, sizeof(sub_shell));
			return -2;
		}
		else
		{
			// ft_printf("{green}started %s %d\n", cmd_env->argv[0], pid);
			// event_exit(0);
			// waitpid(pid, NULL, 0);
			// errno = 0;
			return 0;
		}
	}
	else if (cmd_env->argv[0] != NULL && cmd_is_set_var(cmd_env->argv[0]))
	{
		execute_cmd_set_local_var(cmd_env);
		return 0;
	}
	else if ((exec_cmd_f = get_sh_builtin_f(cmd_env->argv[0], pipe_env->built_in_cmds)))
	{
		execute_built_in(cmd_env, exec_cmd_f);
		return 0;
	}
	else if (cmd_is_specific_program(cmd_env->argv[0]))
		return execute_cmd(cmd_env, cmd_env->argv[0]);
	else if ((cmd_path =
		find_cmd_in_env_path(cmd_env->argv[0], pipe_env->shvars, FALSE)))
	{
		ret = execute_cmd(cmd_env, cmd_path);
		free(cmd_path);
		return ret;
	}
	g_shdata.running_a_process = FALSE;
	ft_error(FALSE, "%s: command not found\n", cmd_env->argv[0]);
	return -1;
}
