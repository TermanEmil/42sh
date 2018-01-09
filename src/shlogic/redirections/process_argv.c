#include "shlogic.h"
#include "shell42.h"

pid_t	process_argv(t_pipe_env *pipe_env, t_cmd_env *cmd_env)
{
	t_str			cmd_path;
	t_exec_cmd_f	*exec_cmd_f;
	pid_t			ret;

	g_shdata.running_a_process = TRUE;
	if (cmd_env->argv[0] != NULL && cmd_is_set_var(cmd_env->argv[0]))
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
	else if ((cmd_path = find_cmd_in_env_path(cmd_env->argv[0], pipe_env->shvars)))
	{
		ret = execute_cmd(cmd_env, cmd_path);
		free(cmd_path);
		return ret;
	}
	g_shdata.running_a_process = FALSE;
	ft_error(FALSE, "%s: command not found\n", cmd_env->argv[0]);
	return -1;
}
