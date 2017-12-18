#include "shinput.h"

/*
** Sets a copy of the given new_seq at history->inputs[i] if everything is
** fine (i is in range, etc).
*/

void	history_change_seq_at(t_input_history * const history,
			t_shinput_seq * const new_seq, int const i)
{
	t_lst_input_seq	*lst_tmp;

	if (i < 0)
		return;

	lst_tmp = ft_lstget(history->inputs, i);
	if (lst_tmp == NULL)
		return;

	shinput_seq_destruct(LCONT(lst_tmp, t_shinput_seq*));
	lst_tmp->content = input_seq_cpy(new_seq);
}
