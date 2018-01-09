#include "shell42.h"

static void			printing_stuff_(
						int y2,
						t_rostr disp_total,
						t_rostr disp_to_cursor)
{
	INTERPT_RETRY(term_cursor_goto(0, y2));
	INTERPT_RETRY(term_clear_from_cursor_to_bot());
	INTERPT_RETRY(ft_putstr(shell_get_prompt()));
	INTERPT_RETRY(ft_putstr(disp_total));

	INTERPT_RETRY(term_cursor_goto(0, y2));
	INTERPT_RETRY(ft_putstr(shell_get_prompt()));
	INTERPT_RETRY(ft_putstr(disp_to_cursor));
}

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
		printing_stuff_(y2, disp_total, disp_to_cursor);
		if ((int)symbols_to_cursor % term_get_width() == term_get_width() - 1)
		{
			ft_putstr("\n");
			term_move_cursor_to_left_most();
		}
		ret = 0;
		errno = 0;
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