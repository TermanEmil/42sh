#include "termlib.h"

void	term_cursor_on(void)
{
	term_tputs("ve", 0, term_get_data()->tmp_buf);
}

void	term_cursor_off(void)
{
	term_tputs("vi", 0, term_get_data()->tmp_buf);
}
