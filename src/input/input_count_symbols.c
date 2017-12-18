#include "shinput.h"

/*
** Counts the number of symbols the first n keys of the given list of keys.
*/

size_t				input_count_symbols(t_lst_inkey const *head,
						ssize_t const start, ssize_t const end)
{
	size_t		result;
	ssize_t		i;

	result = 0;
	i = 0;
	while (head)
	{
		if (i > end)
			break;
		if (i >= start)
			result += sh_inkey_get_symbols(LCONT(head, t_sh_inkey*));
		LTONEXT(head);
		i++;
	}
	return (result);
}
