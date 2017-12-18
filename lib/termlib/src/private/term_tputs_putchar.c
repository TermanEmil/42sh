#include "termlib.h"

/*
** FD_WR determines where the tputs will print everything.
** I'm not sure of it, but it can change some stuff if I print in STDERR instead
** of STDOUT...
*/

int		term_tputs_putchar(int const c)
{
	write(FD_WR, &c, 1);
	return (1);
}
