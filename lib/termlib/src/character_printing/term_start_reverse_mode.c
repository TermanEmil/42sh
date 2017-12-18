#include "termlib.h"

void	term_start_reverse_mode(void)
{
	term_try_tputs("mr", 0, term_get_data()->tmp_buf);
}
