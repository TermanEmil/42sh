#include "shell42.h"

static int			move_to_previos_in_key(int * const x, int * const y,
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

static inline int	process_delim(int * const first_is_delim,
						t_lst_inkey const * const lst_key)
{
	if (sh_inkey_is_delim(LCONT(lst_key, t_sh_inkey*)))
	{
		if (!*first_is_delim)
			return (1);
	}
	else
		*first_is_delim = FALSE;
	return (0);
}

static inline void	custom_input_reprint(int const x, int const y,
						ssize_t const cursor_pos)
{
	term_cursor_goto(x, y);
	g_current_in->cursor_pos = cursor_pos - 1;
	input_reprint(g_current_in);
	g_current_in->cursor_pos = cursor_pos + 1;
	current_input_mv_cursor_pos(-1);
}

int					key_cmd_ctrl_arrow_left(void)
{
	int					x, y;
	t_bool				first_is_delim;
	t_lst_inkey const	*lst_key;
	ssize_t				cursor_pos;

	shell_get_cursor_pos(&x, &y);
	cursor_pos = g_current_in->cursor_pos;
	lst_key = ft_lstget(g_current_in->input->keys, cursor_pos - 1);
	first_is_delim = TRUE;
	while (lst_key != NULL)
	{
		if (process_delim(&first_is_delim, lst_key))
			break;

		if (move_to_previos_in_key(&x, &y, lst_key, &cursor_pos) == -1)
			return (-1);
		
		LTOPREV(lst_key);
	}
	if (lst_key && move_to_previos_in_key(&x, &y, lst_key, &cursor_pos) == -1)
		return (-1);
	custom_input_reprint(x, y, cursor_pos);
	return (0);
}
