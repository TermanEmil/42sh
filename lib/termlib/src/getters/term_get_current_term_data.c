#include "termlib.h"

t_termios	term_get_current_term_data(void)
{
	t_termios	term;

	if (tcgetattr(STDOUT_FILENO, &term) < 0)
		ft_proj_err("couldn't read terminal data", 1);
	return (term);
}

