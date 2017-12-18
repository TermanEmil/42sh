#include "unittest.h"
#include "ft_colors.h"
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "ft_colors.h"

/*
** Processes if the child status had any errors.
*/

static int	process_child_status(int child_status)
{
	if (WTERMSIG(child_status) == SIGSEGV)
	{
		ft_putstr(C_RED "[Seg fault]\n" C_EOC);
		return (139);
	}
	else if (WTERMSIG(child_status) != 0)
	{
		ft_putstr(C_RED "[Terminated, signal: ");
		ft_putnbr(WTERMSIG(child_status));
		ft_putstr("]\n C_EOC");
	}
	else if (WCOREDUMP(child_status))
	{
		ft_putstr(C_RED "[Core dump]\n" C_EOC);
		return (TEST_COREDUMP);
	}
	else if (WEXITSTATUS(child_status) == 0)
		return (0);
	else
		ft_putstr(C_RED "[Error]\n" C_EOC);
	return (1);
}

int		run_test(t_unittest * utest, char * buf, ssize_t buf_len)
{
	int		child_status;
	int		ret;

	get_func_out(utest->f, buf, buf_len, &child_status);
	ft_putstr(utest->f_name);
	ft_putstr(": ");
	if ((ret = process_child_status(child_status)) == 0)
	{
		if (ft_strequ(buf, utest->expected_out))
		{
			ft_putstr(C_GREEN "[OK]\n" C_EOC);
			return (TEST_SUCC);
		}
		else
		{
			ft_putstr(C_RED "[FAIL]\n" C_EOC);
			ft_printf("\t" C_RED "Function output" C_EOC
				":" C_CYAN "%s" C_EOC ":\n", buf);
			return (TEST_FAIL);
		}
	}
	else
		return (ret);
}
