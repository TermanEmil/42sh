#include "shell42.h"

int		key_cmd_home(void)
{
	ssize_t		len;
	int			x, y;
	t_lst_inkey	*lst_key;

	shell_get_cursor_pos(&x, &y);
	len = (ssize_t)x;
	lst_key = ft_lstget(
		g_current_in->input->keys, g_current_in->cursor_pos - 1);
	while (len > 0 && lst_key != NULL)
	{
		len -= sh_inkey_get_symbols(LCONT(lst_key, t_sh_inkey*));
		g_current_in->cursor_pos--;
		LTOPREV(lst_key);
	}
	term_cursor_goto(len, y);
	g_current_in->cursor_pos--;
	input_reprint(g_current_in);
	g_current_in->cursor_pos++;
	return (0);
}
