#include "shinput.h"

void	current_in_resset(t_current_input * const current_in,
			t_bool const destroy_seq)
{
	if (current_in->input)
	{
		if (destroy_seq)
			shinput_seq_destruct(current_in->input);
		else
			free(current_in->input);
	}

	current_in->input = shinput_seq_new();
	current_in->cursor_pos = 0;
}
