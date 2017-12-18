#include "termlib.h"

void	term_move_cursor_to_left_most(void)
{
	term_tputs("cr", 1, term_get_data()->tmp_buf);
}
