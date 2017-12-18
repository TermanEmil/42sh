#include "shell42.h"

void	current_in_handle_sigint(t_shinput * const shinput)
{
	if (!shinput->signaled_sigint)
		return;

	ft_putstr("^C");

	current_in_resset(&shinput->current, TRUE);
	shinput->current.line_index = 0;

	shinput_seq_destruct(shinput->history.tmp_current_in);
	shinput->history.tmp_current_in = NULL;
	shinput->history.current_in_index = -1;

	ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);

	term_putnewl();
	input_reprint_here(&shinput->current);
}
