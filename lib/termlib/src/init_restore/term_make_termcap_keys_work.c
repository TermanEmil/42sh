#include "termlib.h"

/*
** Make that the keyboard transmits what termcap expects.
*/

void	term_make_termcap_keys_work(void)
{
	term_try_tputs("ks", 0, term_get_data()->tmp_buf);
}
