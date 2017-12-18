#include "termlib.h"

void	term_set_current_term_data(t_termios const * const term_to_set)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, term_to_set) < 0)
		ft_proj_err("couldn't change terminal settings", 1);
}
