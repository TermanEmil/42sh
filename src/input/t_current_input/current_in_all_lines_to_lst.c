#include "shinput.h"

static inline void	add_from_history(
						t_lst_inkey ** const head,
						t_input_history * const history,
						int const line_index)
{
	t_lst_input_seq	*lst_seq;
	t_list			*tmp;
	int				i;

	if (line_index <= 0)
		return;

	for (i = line_index - 1; i >= 0; i--)
	{
		lst_seq = ft_lstget(history->inputs, i);
		tmp = ft_lstcpy(LCONT(lst_seq, t_shinput_seq*)->keys);
		if (tmp == NULL)
			ft_err_mem(1);

		ft_lstadd(head, tmp);
		ft_lstadd(head, ft_lstnew(NULL, 0));	
	}
}

static inline void	add_from_seq(
						t_lst_inkey ** const head,
						t_shinput_seq * const seq)
{
	t_list	*cpy;

	cpy = ft_lstcpy(seq->keys);
	if (cpy == NULL && seq->keys != NULL)
		ft_err_mem(1);

	ft_lstadd(head, cpy);
}

t_lst_inkey			*current_in_all_lines_to_lst(t_current_input * const c_in,
						t_input_history * const history)
{
	t_lst_inkey		*result;

	result = NULL;
	add_from_history(&result, history, c_in->line_index);
	add_from_seq(&result, c_in->input);
	return (result);
}
