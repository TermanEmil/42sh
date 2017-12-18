#include "shinput.h"

static void	input_history_pop_last_seq(t_input_history * const target)
{
	if (target->count > 1)
	{
		ft_lstpop_back(&target->inputs, (t_ldel_func*)&shinput_seq_destruct);
		target->count--;
	}
}

void		input_history_add_seq(t_input_history * const target, 
				t_shinput_seq const shinput_seq)
{
	t_list	*tmp;

	if (target)
	{
		tmp = ft_lstnew(&shinput_seq, sizeof(shinput_seq));
		if (tmp == NULL)
			ft_err_mem(1);
		ft_lst_push_front(&target->inputs, tmp);
		target->count++;
		if (target->count > target->nb_of_inputs_to_remember)
			input_history_pop_last_seq(target);
	}
}
