#include "shell42.h"

/*
** Get the newly introduced sequence as a fresh string.
*/

static inline char	*get_input_seq_str(size_t const seq_len)
{
	return (input_seq_get_displayed_range(
		g_current_in->input, g_current_in->cursor_pos - seq_len + 1,
		g_current_in->cursor_pos));
}

/*
** Get the new sequence + what's after it.
*/

static inline char	*get_disp_from_cursor_to_end(size_t const seq_len)
{
	return (input_seq_get_displayed(g_current_in->input,
		g_current_in->cursor_pos - seq_len + 1));
}

/*
** Checks if at the given coordinates, if printed the current input, the
** terminal will scroll everything up with one (or more) lines
*/

static inline t_bool	term_will_add_new_line(int const x, int const y)
{
	size_t	const symbols = input_count_symbols(g_current_in->input->keys,
				g_current_in->cursor_pos - 1, INT_MAX);
	size_t	const total_len = x - 1 + symbols;

	if (y + ((int)total_len - 1) / term_get_width() >= term_get_height())
		return (TRUE);
	else
		return (FALSE);
}

/*
** Manages some stuff when the x coordinate is at the right margin of the
** terminal.
*/

static inline void	process_when_cursor_in_margin(int const x, int const y)
{
	t_sh_inkey	* const key_at_cursor = LCONT(ft_lstget(
					g_current_in->input->keys,
					g_current_in->cursor_pos), t_sh_inkey*);

	if (x == term_get_width() - 1)
	{
		if (char_is_utf8((unsigned char*)key_at_cursor->displayed_chars))
			ft_putstr(key_at_cursor->displayed_chars);
		else
			ft_putstr(" ");
		term_cursor_goto(0, y + 1);
		term_del_char();
	}
}

// term_printf(
// 	-1, -1,
// 	"%d | seq_disp(%s) | at_cursor(%s) | disp(%s) | len(%d) | pos(%d)",
// 	seq_len, seq_disp, key_at_cursor->displayed_chars, disp,
// 	get_shdata()->input.current.input->count, get_shdata()->input.current.cursor_pos);

/*
** Rerprints the data from cursor till the end, arranging the cursor acordingly.
** First I print everyhing from the cursor (including the newly introduced
** sequence) till the end of the input.
** Then, moves back to the starting position and reprints the newly introduced
** sequence, so that the cursor sits acordingly.
**
** It doesn't work if the terminal is in insert mode, that's why I leave this
** mode.
**
** There are some cases, when the cursor sits right in the terminal's ass...
** that is: x >= width (which normally should not be).
*/

void					uinput_print_seq(size_t const seq_len)
{
	int			x, y;
	size_t		const width = term_get_width();
	char		* const disp = get_disp_from_cursor_to_end(seq_len);
	char		* const seq_disp = get_input_seq_str(seq_len);

	term_leave_input_insert_mode();
	shell_get_cursor_pos(&x, &y);
	if (x >= (int)width)
	{
		x = 0;
		y++;
		ft_putstr(" ");
	}

	term_cursor_goto(x, y);
	ft_putstr(disp);
	
	if (term_will_add_new_line(x, y))
		y--;

	term_cursor_goto(x, y);
	ft_putstr(seq_disp);
	process_when_cursor_in_margin(x, y);
	free(disp);
	free(seq_disp);
}