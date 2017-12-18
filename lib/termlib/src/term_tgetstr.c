#include "termlib.h"

char const	*term_tgetstr(char const * const attr)
{
	char	* buf;

	buf = term_get_data()->tmp_buf;
	return (tgetstr(attr, &buf));
}
