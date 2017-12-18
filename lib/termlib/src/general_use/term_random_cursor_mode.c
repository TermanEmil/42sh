#include "termlib.h"

/*
** Makes the the terminal go into a "full screen" mode?
** If you use '| less' command on something, the text will be printed
** somewhere else, right? This does that job.
*/

void				term_random_cursor_mode_on(void)
{
	term_tputs("ti", term_get_height(), term_get_data()->tmp_buf);	
}

void				term_random_cursor_mode_off(void)
{
	term_tputs("te", term_get_height(), term_get_data()->tmp_buf);	
}