#include "shell42.h"

/*
** Not currently used.
** It was meant to be used to reprint the input, when the prompt doesn't fit
** in the terminal's window
*/
/*
void	input_print_last_n_symbols(t_lst_inkey const *key, size_t n)
{
	t_lst_inkey		*cpy, *start;
	size_t			tmp_len;
	char			result[n * 5];
	char			buf[64];
	int				ret;
	size_t			total_len;

	cpy = ft_lstcpy(key);
	if (cpy == NULL)
		ft_err_mem(1);
	ft_bzero(result, sizeof(result));
	ft_lstreverse(&cpy);
	start = cpy;
	total_len = 0;
	while (n && cpy)
	{
		tmp_len = sh_inkey_get_symbols(LCONT(cpy, t_sh_inkey*));
		if (tmp_len > n)
		{
			ft_strncpy(buf, LCONT(cpy, t_sh_inkey*)->displayed_chars + tmp_len - n, n);
			buf[n] = 0;
			n = 0;
		}
		else
		{
			ft_strcpy(buf, LCONT(cpy, t_sh_inkey*)->displayed_chars);
			n -= tmp_len;
		}
		total_len += ft_strlen(buf);
		ret = ft_str_stack_cat(result, buf, sizeof(result) - 1);
		if (ret != 0)
			break;
		LTONEXT(cpy);
	}
	ft_lstdel(&cpy, NULL);
	ft_putstr(result + sizeof(result) - total_len - 1);
}
*/

static inline int	actually_reprint(
						int const lines_up, int const y1,
						t_current_input const * const current_in,
						size_t const symbols_to_cursor)
{
	char	* const disp_total = input_seq_get_displayed(current_in->input, 0);
	char	* const disp_to_cursor = input_seq_get_displayed_range(
				current_in->input, 0, current_in->cursor_pos);

	int		y2;
	int		ret;


	y2 = y1 - lines_up;
	if (y1 >= lines_up)
	{
		term_cursor_goto(0, y2);
		term_clear_from_cursor_to_bot();
		ft_putstr(shell_get_prompt());
		ft_putstr(disp_total);

		term_cursor_goto(0, y2);
		ft_putstr(shell_get_prompt());
		ft_putstr(disp_to_cursor);
		if ((int)symbols_to_cursor % term_get_width() == term_get_width() - 1)
		{
			ft_putstr("\n");
			term_move_cursor_to_left_most();
		}
		ret = 0;
	}
	else
		ret = -1;

	free(disp_total);
	free(disp_to_cursor);
	return (ret);
}

/*
** Reprints the current input.
*/

int					input_reprint(t_current_input const * const current_in)
{
	int		x1, y1;
	size_t	const width = term_get_width();
	size_t	const symbols_to_cursor = input_count_symbols(
				current_in->input->keys, 0, current_in->cursor_pos - 1)
				+ ft_strlen(shell_get_prompt());

	shell_get_cursor_pos(&x1, &y1);

	if (x1 == (int)width)
	{
		x1 = 0;
		y1++;
	}

	return (actually_reprint((width - x1 + symbols_to_cursor - 1) / width,
		y1, current_in, symbols_to_cursor));
}


int					input_reprint_here(t_current_input const * const current_in)
{
	int		x, y;
	size_t	const symbols_to_cursor = input_count_symbols(
				current_in->input->keys, 0, current_in->cursor_pos - 1)
				+ ft_strlen(shell_get_prompt());

	shell_get_cursor_pos(&x, &y);
	return (actually_reprint(0, y, current_in, symbols_to_cursor));
}