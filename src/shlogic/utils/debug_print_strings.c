#include "shlogic.h"
#include "shell42.h"

void	debug_print_strings(t_str *strings, int top_start)
{
	int		i;

	if (strings == NULL)
		return;

	for (i = 0; strings[i]; i++)
		term_printf(0, top_start + i, "%d) %s", i, strings[i]);
	term_printf(0, top_start + i, "--------");
}
