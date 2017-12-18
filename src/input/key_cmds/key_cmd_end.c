#include "shell42.h"

int		key_cmd_end(void)
{
	size_t		len;
	int			x, y;
	t_lst_inkey	*lst_key;

	shell_get_cursor_pos(&x, &y);
	len = x;
	lst_key = ft_lstget(g_current_in->input->keys, g_current_in->cursor_pos);
	while ((int)len < term_get_width() - 1 && lst_key != NULL)
	{
		len += sh_inkey_get_symbols(LCONT(lst_key, t_sh_inkey*));
		g_current_in->cursor_pos++;
		LTONEXT(lst_key);
	}
	term_cursor_goto(len, y);
	g_current_in->cursor_pos--;
	input_reprint(g_current_in);
	g_current_in->cursor_pos++;
	return (0);
}
