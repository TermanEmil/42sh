#include "termlib.h"

void	term_clear_from_cursor_to_end_line(void)
{
	term_tputs("ce", 1, term_get_data()->tmp_buf);
}
