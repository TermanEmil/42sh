#include "termlib.h"

/*
** Exits from dark, reverse, etc modes
*/

void	term_end_standout_mode(void)
{
	term_try_tputs("se", 0, term_get_data()->tmp_buf);
}