#include "termlib.h"

/*
** Puts the cursor at x and y position on the screen.
*/

void	term_cursor_goto(int const x, int const y)
{
	term_tgoto_call("cm", 0, x, y);
}
