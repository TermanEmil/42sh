#include "termlib.h"

void		term_save_current_term_data(void)
{
	term_get_data()->old_term = term_get_current_term_data();
}
