#include "termlib.h"

void	term_enter_input_insert_mode(void)
{
	term_try_tputs("im", 0, term_get_data()->tmp_buf);
}

void	term_leave_input_insert_mode(void)
{
	term_try_tputs("ei", 0, term_get_data()->tmp_buf);
}
