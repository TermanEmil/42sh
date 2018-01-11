#include "shell_redirs_.h"

/*
** First process the pipe redirections then the file redirections, because
** file redirections will be able to overwrite the pipes.
*/

void	process_redirections(t_pipe_env *pipe_env, t_cmd_env *cmd_env)
{
	if (!L_IS_LAST(cmd_env->pipe_queue_iter))
	{
		if (pipe(cmd_env->piped_fds) == -1)
			ft_err_erno(errno, TRUE);
	}

	if (cmd_env->success)
		process_pipe_redirs(cmd_env, pipe_env->current_pipe_input_fd);

	if (cmd_env->success)
		process_all_guillemet_redirs(pipe_env, cmd_env);

	pipe_env->current_pipe_input_fd = cmd_env->piped_fds[PIPE_READ_END];
}
