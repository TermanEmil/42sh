#include "termlib.h"

void		term_enable_raw_mode(t_term_data * const term_data)
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
