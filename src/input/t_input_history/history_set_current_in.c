#include "shinput.h"
#include "termlib.h"

void	history_set_current_in(t_input_history * const history,
			t_current_input * const current_in, int i)
{
	t_lst_input_seq	*tmp;
	t_shinput_seq	*seq;

	if (i == -1)
	{
		seq = history->tmp_current_in;
		history->tmp_current_in = NULL;
	}
	else
	{
		tmp = ft_lstget(history->inputs, i);
		if (tmp == NULL)
			return;

		seq = input_seq_cpy(LCONT(tmp, t_shinput_seq*));

		if (history->tmp_current_in == NULL)
			history->tmp_current_in = input_seq_cpy(current_in->input);
	}

	term_cursor_off();

	input_mv_cursor_at_start(current_in);

	if (current_in->input)
		shinput_seq_destruct(current_in->input);
	
	current_in->input = seq;
	current_in->cursor_pos = seq->count;
	history->current_in_index = i;

	input_reprint_here(current_in);
	term_cursor_on();
}