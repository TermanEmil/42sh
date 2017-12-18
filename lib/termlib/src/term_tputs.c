#include "termlib.h"

/*
** I just followed the manual and gave it buf.
** It seems that tgetstr allocates memory in a static pointer, only once.
*/

void	term_tputs(char const *attr_name, size_t const nlines, char *buf)
{
	char * const str_attr = tgetstr(attr_name, &buf);

	if (str_attr == NULL)
		ft_fatal("%s: doesn't support `%s' terminal attribute.",
			g_proj_name, attr_name);
	tputs(str_attr, nlines, &term_tputs_putchar);
}

/*
** Doesn't throw any errors
*/

void	term_try_tputs(char const *attr_name, size_t const nlines, char *buf)
{
	char * const str_attr = tgetstr(attr_name, &buf);

	if (str_attr == NULL)
		return;
	tputs(str_attr, nlines, &term_tputs_putchar);	
}