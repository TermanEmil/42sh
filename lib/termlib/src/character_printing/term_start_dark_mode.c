#include "termlib.h"

/*
** Invisible characters
*/

void	term_start_dark_mode(void)
{
	term_try_tputs("mk", 0, term_get_data()->tmp_buf);
}
