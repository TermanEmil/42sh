#include "termlib.h"

t_term_data	*term_get_data(void)
{
	static t_term_data	data;

	return (&data);
}
