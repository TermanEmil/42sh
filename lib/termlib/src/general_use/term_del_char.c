#include "termlib.h"

/*
** Removes the a character at the cursor position, without changing
** the position of the cursor.
*/

void	term_del_char(void)
{
	term_tputs("dc", 1, term_get_data()->tmp_buf);
}
