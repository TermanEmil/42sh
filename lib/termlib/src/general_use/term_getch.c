#include "termlib.h"

/*
** It's very much like the getch function, but it reads a string in canonical
** form, up to 64 bytes and returns a static pointer of it.
*/

char	*term_getch(void)
{
	t_termios	term;
	t_termios	old_term;
	static char	buf[64];
	ssize_t		ret;

	term = term_get_current_term_data();
	old_term = term;
	term_echo_off_write(&term);
	term_enable_canonical_form_write(&term);
	term_set_current_term_data(&term);
	ret = read(STDIN_FILENO, buf, sizeof(buf) - 1);
	if (ret == -1)
		return (NULL);
	buf[ret] = 0;
	term_echo_restore_write(&term, &old_term);
	term_restore_canonical_form_write(&term, &old_term);
	term_set_current_term_data(&term);
	return (buf);
}
