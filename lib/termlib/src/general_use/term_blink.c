#include "termlib.h"

/*
** Makes the terminal to white blink
*/

void	term_blink(void)
{
	term_try_tputs("vb", 0, term_get_data()->tmp_buf);
}
