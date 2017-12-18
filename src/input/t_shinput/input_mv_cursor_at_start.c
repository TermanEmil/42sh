#include "shell42.h"

static int	move_to_prev(int * const x, int * const y,
				t_lst_inkey const * const lst_key, ssize_t * const cursor_pos)
{
	*x -= sh_inkey_get_symbols(LCONT(lst_key, t_sh_inkey*));

	while (*x < 0)
	{
		*x = (term_get_width() - 1) - *x;
		*y -= 1;
		if (*y < 0)
			return (-1);
	}
	*cursor_pos -= 1;
	return (0);
}

static inline void	custom_input_reprint(int const x, int const y,
						ssize_t const cursor_pos,
						t_current_input * const current_in)
{
	term_cursor_goto(x, y);
	current_in->cursor_pos = cursor_pos - 1;
	input_reprint(current_in);
	current_in->cursor_pos = cursor_pos + 1;
	current_input_mv_cursor_pos(-1);
}

void	input_mv_cursor_at_start(t_current_input * const current_in)
{
	ssize_t		cursor_pos;
	int			x, y;
	t_lst_inkey	*lst_key;

	shell_get_cursor_pos(&x, &y);
	cursor_pos = current_in->cursor_pos;
	lst_key = ft_lstget(current_in->input->keys, current_in->cursor_pos - 1);
	while (lst_key != NULL)
	{
		if (move_to_prev(&x, &y, lst_key, &cursor_pos) == -1)
			return;

		LTOPREV(lst_key);
	}
	custom_input_reprint(x, y, cursor_pos, current_in);
}
