#include "termlib.h"

/*
** Generally it restores to the old_term
*/

void	term_restore(t_termios const *old_term)
{
	// t_termios	term;

	// term = term_get_current_term_data();
	// term_restore_canonical_form_write(&term, old_term);
	// term_echo_restore_write(&term, old_term);
	term_set_current_term_data(old_term);
	term_cursor_on();
}
