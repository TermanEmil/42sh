#include "termlib.h"

/*
** Termtype is the `getenv("TERM")'
** Setups the terminal and makes it enter the canonical form and making
** the input invisible (echo off)
** Ex: term_setup(getenv("TERM"), term_get_data());
*/

void		term_setup(char const *termtype, t_term_data * const term_data)
{
	term_init_internal_data(termtype, term_data->term_buf);
	term_enable_raw_mode(term_data);
}

