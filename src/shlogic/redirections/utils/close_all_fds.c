#include "shell_redirs_.h"

static void	close_fd_lst_element_(const t_list *lst_fd)
{
	TMP_FAIL_RETRY(close(*LCONT(lst_fd, int*)));
	errno = 0;
}

void		close_all_fds(
				const t_lst_int *fds_to_close, const int *fd, int cmd_count)
{
	int	i;

	ft_lstiter((t_list*)fds_to_close, (void (*)(t_list*))&close_fd_lst_element_);
	for (i = 0; i < cmd_count; i++)
	{
		if (fd[i * 2 + PIPE_READ_END] != -1)
			TMP_FAIL_RETRY(close(fd[i * 2 + PIPE_READ_END]));
		errno = 0;
	}
}
