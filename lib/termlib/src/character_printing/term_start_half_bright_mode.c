#include "termlib.h"

void	term_start_half_bright_mode(void)
{
	term_try_tputs("mh", 0, term_get_data()->tmp_buf);
}
