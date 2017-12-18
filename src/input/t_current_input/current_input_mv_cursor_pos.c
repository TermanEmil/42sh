#include "shell42.h"

/*
** Atempts to move the cursor_pos with delta value.
** The cursor_pos is limited: [0, `input.current.input->count`]
*/

int		current_input_mv_cursor_pos(ssize_t const delta)
{
	if (g_current_in->cursor_pos + delta < 0)
	{
		g_current_in->cursor_pos = 0;
		return (-1);	
	}
	else if (g_current_in->cursor_pos + delta >
		(ssize_t)g_current_in->input->count)
	{
		g_current_in->cursor_pos = g_current_in->input->count;
		return (1);
	}
	else
	{
		g_current_in->cursor_pos += delta;
		return (0);
	}
}
