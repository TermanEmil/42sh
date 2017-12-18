#include "shell42.h"

int		key_cmd_arrow_up(void)
{
	history_change_seq_at(&g_shinput->history, g_current_in->input,
		g_shinput->history.current_in_index);

	history_set_current_in(&g_shinput->history, g_current_in,
		g_shinput->history.current_in_index + 1);
	
	return (0);
}
