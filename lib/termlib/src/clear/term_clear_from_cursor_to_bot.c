#include "termlib.h"

void	term_clear_from_cursor_to_bot(void)
{
	term_tputs("cd", term_get_height(), term_get_data()->tmp_buf);
}
