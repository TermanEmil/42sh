#include "shell_redirs_.h"
#include "shell42.h"

/*
** If the next pipe is a |&, then stderr should redirectionate to stdout.
*/

static t_bool	pipe_should_redir_stderr_(const t_grps_wrds *next_group)
{
	const t_lst_words	*words;

	if (next_group->next == NULL)
		return FALSE;

	words = LCONT(next_group->next, t_lst_words*);
	return words_match_single(words, "\\|&");
}

void			process_pipe_redirs(
					t_cmd_env *cmd_env,
					int current_pipe_input_fd)
{
	cmd_env->fd_io.in = current_pipe_input_fd;
	if (L_IS_LAST(cmd_env->pipe_queue_iter))
		cmd_env->fd_io.out = STDOUT_FILENO;
	else
		cmd_env->fd_io.out = cmd_env->piped_fds[PIPE_WRITE_END];

	if (pipe_should_redir_stderr_(cmd_env->pipe_queue_iter))
		cmd_env->fd_io.err = STDOUT_FILENO;
	else
		cmd_env->fd_io.err = STDERR_FILENO;
}
