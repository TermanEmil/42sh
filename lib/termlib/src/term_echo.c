#include "termlib.h"

/*
** The enetered keys are not printed.
** Writes this option in the given term
*/

void		term_echo_off_write(t_termios * const term)
{
	term->c_lflag &= ~(ECHO);
}

/*
** Applies echo off imediately
*/

void		term_echo_off(void)
{
	t_termios	term;

	term = term_get_current_term_data();
	term_echo_off_write(&term);
	term_set_current_term_data(&term);
}

void		term_echo_restore_write(
				t_termios * const term,
				t_termios const *old_term)
{
	term->c_lflag |= old_term->c_lflag & ECHO;
}

void		term_echo_restore(void)
{
	t_termios	term;

	term = term_get_current_term_data();
	term_echo_restore_write(&term, &term_get_data()->old_term);
	term_set_current_term_data(&term);
}
