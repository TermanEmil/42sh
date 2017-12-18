#include "shell42.h"

static inline int	process_coords(int * const x, int * const y,
						t_lst_inkey const * const lst_key)
{
	*x -= sh_inkey_get_symbols(LCONT(lst_key, t_sh_inkey*));
		
	while (*x < 0)
	{
		*x = (term_get_width() - 1) - *x;
		*y -= 1;
		if (*y < 0)
			return (-1);
	}
	return (0);
}

static inline void	custom_reprint(int const x, int const y,
						ssize_t const cursor_pos)
{
	term_cursor_goto(x, y);
	g_current_in->cursor_pos = cursor_pos - 1;
	input_reprint(g_current_in);
	g_current_in->cursor_pos = cursor_pos + 1;
	g_current_in->cursor_pos--;
}

int		key_cmd_alt_up(void)
{
	int					start_x, x, start_y, y;
	t_lst_inkey const	*lst_key;
	ssize_t				cursor_pos;

	shell_get_cursor_pos(&start_x, &start_y);
	if (start_y <= 0)
		return (-1);
	cursor_pos = g_current_in->cursor_pos;
	lst_key = ft_lstget(g_current_in->input->keys, cursor_pos - 1);
	x = start_x;
	y = start_y;
	while (lst_key && !(x <= start_x + 1 && y < start_y))
	{
		if (process_coords(&x, &y, lst_key) == -1)
			return (-1);

		cursor_pos--;
		LTOPREV(lst_key);
	}
	custom_reprint(x, y, cursor_pos);
	return (0);
}
