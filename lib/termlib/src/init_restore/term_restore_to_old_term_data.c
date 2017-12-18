#include "termlib.h"

/*
** Restores the terminal to the term_get_data()->old_term
*/

void		term_restore_to_old_term_data(void)
{
	term_restore(&term_get_data()->old_term);
}
