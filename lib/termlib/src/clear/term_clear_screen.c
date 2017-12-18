#include "termlib.h"

/*
** Use tgetent before using this function
*/

void	term_clear_screen(void)
{
	term_tputs("cl", 1, term_get_data()->tmp_buf);
}
