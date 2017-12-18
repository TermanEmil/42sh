#include "termlib.h"

/*
** Puts the cursor in the left top corner
*/

void	term_cursor_goto_home(void)
{
	term_tputs("ho", 0, term_get_data()->tmp_buf);
}
