#include "termlib.h"

void	term_scroll_up(void)
{
	term_tputs("sf", term_get_height(), term_get_data()->tmp_buf);	
}

void	term_scroll_down(void)
{
	term_tputs("sr", term_get_height(), term_get_data()->tmp_buf);	
}
