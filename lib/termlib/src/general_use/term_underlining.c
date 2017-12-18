#include "termlib.h"

void	term_start_underlining(void)
{
	term_try_tputs("us", 0, term_get_data()->tmp_buf);
}

void	term_end_underlining(void)
{
	term_try_tputs("ue", 0, term_get_data()->tmp_buf);
}
