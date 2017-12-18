#include "shinput.h"

static inline size_t	get_history_mean_len(t_input_history const * const hist,
							size_t const delim_len)
{
	size_t			result;
	t_lst_input_seq	*lst_input_seq;

	lst_input_seq = hist->inputs;
	result = 0;
	while (lst_input_seq)
	{
		result += ft_strlen(input_seq_get_meaning(
			LCONT(lst_input_seq, t_shinput_seq*), 0));
		result += delim_len;
		LTONEXT(lst_input_seq);
	}
	return (result);
}

t_str					debug_get_history(t_input_history const * const hist)
{
	t_str	result;
	t_lst_input_seq	*lst_input_seq;

	result = ft_strnew_raw(get_history_mean_len(hist, ft_strlen("; ")));
	if (result == NULL)
		ft_err_mem(1);

	lst_input_seq = hist->inputs;
	while (lst_input_seq)
	{
		ft_strcat(result, input_seq_get_meaning(
			LCONT(lst_input_seq, t_shinput_seq*), 0));
		ft_strcat(result, "; ");
		LTONEXT(lst_input_seq);
	}
	return (result);
}
