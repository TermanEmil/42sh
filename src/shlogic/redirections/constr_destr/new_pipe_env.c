#include "shell_redirs_.h"

t_pipe_env	new_pipe_env(
				const t_grps_wrds *pipe_queue,
				const t_hashtab *built_in_cmds,
				t_shvars *shvars)
{
	t_pipe_env	result;

	result.pipe_queue = pipe_queue;
	result.built_in_cmds = built_in_cmds;
	result.shvars = shvars;

	result.current_pipe_input_fd = STDIN_FILENO;
	result.cmd_count = ft_lstlen(pipe_queue);
	result.fds_to_close = NULL;
	return result;
}
