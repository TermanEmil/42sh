#include "shell_redirs_.h"

t_cmd_env	new_cmd_env(
				t_str *argv,
				const t_grps_wrds *pipe_queue_iter,
				t_shvars *shvars,
				int *piped_fds)
{
	t_cmd_env	result;

	result.argv = argv;
	result.pipe_queue_iter = pipe_queue_iter;
	result.piped_fds = piped_fds;
	result.shvars = shvars;

	result.fd_io.in = STDIN_FILENO;
	result.fd_io.out = STDOUT_FILENO;
	result.fd_io.err = STDERR_FILENO;
	result.fd_io.other = NULL;
	result.success = TRUE;
	return result;
}
