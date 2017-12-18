#include "termlib.h"

static void	enable_raw_mode(t_term_data * const term_data)
{
	t_termios	term;

	term = term_get_current_term_data();
	term_data->old_term = term;
	term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
							| INLCR | IGNCR | ICRNL | IXON);
	term.c_oflag &= ~OPOST;
	term.c_lflag &= ~(ECHO | ECHONL | ICANON //| ISIG
					| IEXTEN | TOSTOP);
	term.c_cflag &= ~(CSIZE | PARENB);
	term.c_cflag |= CS8;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term_set_current_term_data(&term);
}

/*
** Termtype is the `getenv("TERM")'
** Setups the terminal and makes it enter the canonical form and making
** the input invisible (echo off)
** Ex: term_setup(getenv("TERM"), term_get_data());
*/

void		term_setup(char const *termtype, t_term_data * const term_data)
{
	// t_termios	term;

	term_init_internal_data(termtype, term_data->term_buf);
	// term = term_get_current_term_data();
	// term_data->old_term = term;
	// term_enable_canonical_form_write(&term);
	// term_echo_off_write(&term);
	// term_set_current_term_data(&term);
	enable_raw_mode(term_data);
}