#include "unittest.h"
#include "ft_errors.h"
#include "ft_colors.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
** Source: http://www.microhowto.info/howto/
** capture_the_output_of_a_child_process_in_c.html
*/

static int	its_child_process(pid_t father)
{
	return (father == 0);
}

static int	its_main_process(pid_t father)
{
	return (father > 0);
}

/*
** The reading is performed only once, so make sure the buf is large enough
*/

static void	read_from_pipe(int fd, char * buf, ssize_t buf_len)
{
	ssize_t	count;

	count = read(fd, buf, buf_len);
	if (count == -1)
		ft_fatal("Failed to read\n");
}

static void	init_get_func_out(pid_t *pid, int *fields, char *buf, size_t blen)
{
	if (pipe(fields) == -1)
		ft_fatal("Failed to pipe\n");
	*pid = fork();
	if (*pid == -1)
		ft_fatal("Failed to fork\n");
	ft_bzero(buf, blen);
}

/*
** The effect is to close the file descriptor STDOUT_FILENO if it was
** previously open, then (re)open it as a copy of filedes[1]. A loop is
** needed to allow for the possibility of dup2 being interrupted by a signal.
** Once this has been done, filedes[1] can be closed
*/

void		get_func_out(func_utest *f, char * buf, ssize_t buf_len,
				int * child_status)
{
	pid_t	pid;
	int		fields[2];

	init_get_func_out(&pid, fields, buf, buf_len);
	if (its_child_process(pid))
	{
		while (dup2(fields[1], STDOUT_FILENO) == -1 && errno == EINTR);
		while (dup2(fields[1], STDERR_FILENO) == -1 && errno == EINTR);
		close(fields[0]);
		close(fields[1]);
		f();
		exit(0);
	}
	else if (its_main_process(pid))
	{
		close(fields[1]);
		if (wait(child_status) == -1)
			ft_fatal("Failed to wait for process\n");
		read_from_pipe(fields[0], buf, buf_len);
		close(fields[0]);
	}
}
