#include "termlib.h"

/*
** Clears n characters starting from the current cursor position
*/

void	term_clear_n_chars(size_t const n)
{
	term_tgoto_call("ec", 1, 0, n);
}
