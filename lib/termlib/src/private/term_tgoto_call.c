#include "termlib.h"

/*
** Private.
** A termcap function used to print capabilities with parameters.
*/

void	term_tgoto_call(char const *attr, size_t const nlines,
			int const x, int const y)
{
	char 			*buf;

	buf = term_get_data()->tmp_buf;

	char const		*attr_str = tgetstr(attr, &buf);

	if (attr_str == NULL)
		ft_fatal("%s: doesn't support `%s' terminal attribute.",
			g_proj_name, attr);

	char const		*tgoto_str = tgoto(attr_str, x, y);

	if (tgoto_str == NULL)
		ft_fatal("%s: doesn't support `tgoto()' functionality.", g_proj_name);
	tputs(tgoto_str, nlines, &term_tputs_putchar);
}
