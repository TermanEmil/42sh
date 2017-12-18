#include "termlib.h"

/*
** Enables the canonical form.
** It means that instead of waiting for an enter to process the data,
** it will process each key.
** Try enabling canonincal form and then run ft_getch().
** VMIN == the minimum length to expect.
** VTIME == the time to wait...
*/

void		term_enable_canonical_form_write(t_termios * const term)
{
	term->c_lflag &= ~(ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
}

void		term_enable_canonical_form(void)
{
	t_termios	term;

	term = term_get_current_term_data();
	term_enable_canonical_form_write(&term);
	term_set_current_term_data(&term);
}

/*
** Restores to canonical form to the previous form.
*/

void		term_restore_canonical_form_write(
				t_termios * const term,
				t_termios const *old_term)
{
	term->c_lflag |= old_term->c_lflag & ICANON;
	term->c_cc[VMIN] = old_term->c_cc[VMIN];
	term->c_cc[VTIME] = old_term->c_cc[VTIME];
}

void		term_restore_canonical_form(void)
{
	t_termios	term;

	term = term_get_current_term_data();
	term_restore_canonical_form_write(&term, &term_get_data()->old_term);
	term_set_current_term_data(&term);
}
