#include "shinput.h"

void			input_mv_current_in_to_history(t_shinput * const input)
{
	input_history_add_seq(&input->history, *input->current.input);
	current_in_resset(&input->current, FALSE);
}
