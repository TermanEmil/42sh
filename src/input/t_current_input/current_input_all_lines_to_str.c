#include "shinput.h"

static t_rostr const	g_err_null_history_element =
							"Internal error: current_in_count_str() - "
							"current_input_is_complete() - null elemnet";

static inline size_t	current_in_count_str_len(
							t_current_input const * const current_in,
							size_t const delim_len)
{
	size_t					result;
	int						i;
	t_lst_input_seq const	*lst_input_seq;
	int	count = 0;

	result = input_seq_get_meaning_len(current_in->input, 0);
	if (current_in->line_index > 0)
	{
		for (i = current_in->line_index - 1; i >= 0; i--)
		{
			count++;
			lst_input_seq = ft_lstget(g_shinput->history.inputs, i);
			if (lst_input_seq == NULL)
				ft_fatal(g_err_null_history_element);

			result += delim_len;
			result += input_seq_get_meaning_len(
				LCONT(lst_input_seq, t_shinput_seq*), 0);
		}
	}
	return (result);
}		

static inline void		current_in_save_to_str(
							t_current_input const * const current_in,
							t_str const buf,
							t_rostr const delim)
{
	t_str					tmp;
	int						i;
	t_lst_input_seq const	*lst_input_seq;

	buf[0] = 0;
	if (current_in->line_index > 0)
	{
		for (i = current_in->line_index - 1; i >= 0; i--)
		{
			lst_input_seq = ft_lstget(g_shinput->history.inputs, i);
			
			if (lst_input_seq == NULL)
				ft_fatal(g_err_null_history_element);
			
			tmp = input_seq_get_meaning(
				LCONT(lst_input_seq, t_shinput_seq*), 0);

			ft_strcat(buf, tmp);
			ft_strcat(buf, delim);
			free(tmp);
		}
	}
	tmp = input_seq_get_meaning(current_in->input, 0);
	ft_strcat(buf, tmp);
	free(tmp);
}

/*
** Current input may consist of multiple lines.
*/

char	*current_input_all_lines_to_str(
			t_current_input const * const current_in,
			t_rostr const delim)
{
	t_str	result;

	result = ft_strnew_raw(current_in_count_str_len(current_in,
		ft_strlen(delim)));

	if (result == NULL)
		ft_err_mem(1);
	
	current_in_save_to_str(current_in, result, delim);
	return (result);
}
