#include "shell_redirs_.h"
#include "regex_tools.h"
#include <fcntl.h>

static void	assign_default_left_redir_value_(
				int dest_fd,
				t_cmd_env *cmd_env,
				const t_redir_env *redir_env)
{
	if (ft_strequ(redir_env->redir_type, "<"))
		cmd_env->fd_io.in = dest_fd;
	else
		cmd_env->fd_io.out = dest_fd;
}

static int	open_redir_file_(const t_redir_env *redir_env)
{
	int		open_flags;
	int		fd;

	if (ft_strchr(redir_env->redir_type, '>'))
	{
		open_flags = O_WRONLY | O_CREAT;
		if (ft_strequ(redir_env->redir_type, ">>"))
			open_flags |= O_APPEND;
		else
			open_flags |= O_TRUNC;
	}
	else
		open_flags = O_RDONLY;
	
	fd = TMP_FAIL_RETRY(open(redir_env->next_word_str, open_flags, 0644));
	return fd;
}

static int	get_destination_fd_(
				t_cmd_env *cmd_env,
				t_redir_env *redir_env)
{
	int		dest_fd;

	if (redir_env->right_fd >= 0)
		return redir_env->right_fd;

	if (redir_env->next_word_str == NULL)
	{
		ft_error(FALSE, "%s: %s: %s\n",
			g_proj_name, redir_env->redir, "No file specified");
		errno = 0;
		cmd_env->success = FALSE;
		return -1;
	}

	dest_fd = open_redir_file_(redir_env);
	if (dest_fd == -1)
	{
		ft_error(FALSE, "%s: %s: %s\n",
			g_proj_name, redir_env->next_word_str, strerror(errno));
		errno = 0;
		cmd_env->success = FALSE;
		return -1;
	}
	return dest_fd;
}

void		process_guillemet_redir_to_from_file(
				t_pipe_env *pipe_env,
				t_cmd_env *cmd_env,
				t_redir_env *redir_env)
{
	int			dest_fd;
	t_to_dup	to_dup;

	if (!regex_mini_match("(^>$|^>>$|^<$)", redir_env->redir_type))
	{
		ft_error(FALSE, "%s: %s: invalid redirection\n",
			g_proj_name, redir_env->redir);
		cmd_env->success = FALSE;
		return;
	}

	if ((dest_fd = get_destination_fd_(cmd_env, redir_env)) == -1)
		return;
	
	if (redir_env->left_fd >= 0)
	{
		to_dup = new_to_dup(dest_fd, redir_env->left_fd, FALSE);
		ft_lstadd(&cmd_env->fd_io.other, ft_lstnew(&to_dup, sizeof(to_dup)));
	}
	else
		assign_default_left_redir_value_(dest_fd, cmd_env, redir_env);

	if (redir_env->right_fd < 0)
		ft_lstadd(&pipe_env->fds_to_close, ft_lstnew(&dest_fd, sizeof(int)));
}
