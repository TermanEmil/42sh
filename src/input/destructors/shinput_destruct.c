#include "shinput.h"

void		shinput_destruct(t_shinput * const target)
{
	if (target)
	{
		current_input_destruct(&target->current);
		input_history_destruct(&target->history);
		if (target->term_tty > 0)
			close(target->term_tty);
	}
}
