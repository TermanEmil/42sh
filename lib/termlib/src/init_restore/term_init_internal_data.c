#include "termlib.h"

/*
** Called before using any termcap functionality
** Termtype represents the TERM enviroment var, use `getenv("TERM")'
** The term_buf must not be modified during the entire use of this tgetent.
*/

void	term_init_internal_data(char const *termtype, char * const term_buf)
{
	if (termtype == NULL)
		ft_fatal("Speciy a terminal type with `setenv TERM <yourtype>'.");
	int const success = tgetent(term_buf, termtype);
	if (success < 0)
		ft_fatal("Could not access the termcap data base.");
	if (success == 0)
		ft_fatal("Terminal type `%s' is not defined.", termtype);
}
