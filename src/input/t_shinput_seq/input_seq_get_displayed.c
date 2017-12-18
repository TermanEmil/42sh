#include "shinput.h"
#include "termlib.h"
/*
** Returns a fresh string with the displayable characters
*/

char	*input_seq_get_displayed(t_shinput_seq const * const seq,
			size_t const starting_with)
{
	char		*result;
	size_t		i;
	t_lst_inkey	*aux;

	result = ft_strnew(input_seq_get_disp_len(seq, starting_with));
	if (result == NULL)
		ft_err_mem(1);
	aux = seq->keys;
	i = 0;
	while (aux)
	{
		if (i >= starting_with)
			ft_strcat(result, LCONT(aux, t_sh_inkey*)->displayed_chars);
		LTONEXT(aux);
		i++;
	}
	return (result);
}

static size_t	input_seq_get_displayed_range_len(
					t_shinput_seq const * const seq,
					ssize_t const start, ssize_t const end)
{
	ssize_t		rs_len;
	ssize_t		i;
	t_lst_inkey	*aux;

	rs_len = 0;
	aux = seq->keys;
	i = 0;
	while (aux)
	{
		if (i > end)
			return (rs_len);
		if (i >= start)
			rs_len += ft_strlen(LCONT(aux, t_sh_inkey*)->displayed_chars);
		i++;
		LTONEXT(aux);
	}
	return (rs_len);
}

char			*input_seq_get_displayed_range(t_shinput_seq const * const seq,
					ssize_t const start, ssize_t const end)
{
	char		* const result = ft_strnew(
					input_seq_get_displayed_range_len(seq, start, end));

	ssize_t		i;
	t_lst_inkey	*aux;

	if (result == NULL)
		ft_err_mem(1);
	aux = seq->keys;
	i = 0;
	while (aux)
	{
		if (i > end)
			break;
		if (i >= start)
			ft_strcat(result, LCONT(aux, t_sh_inkey*)->displayed_chars);
		i++;
		LTONEXT(aux);
	}
	return (result);
}