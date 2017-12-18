#include "shinput.h"

void			input_history_destruct(t_input_history * const target)
{
	if (target)
	{
		ft_lstdel(&target->inputs, (t_ldel_func*)&shinput_seq_destruct);

		if (target->tmp_current_in)
			shinput_seq_destruct(target->tmp_current_in);
	}
}
