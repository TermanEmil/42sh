#include "listlib.h"
#include <limits.h>

/*
** Join an entire list of objects, in a single string.
*/

t_str	ft_lst_join(
			t_list const *list,
			t_rostr (*get_str)(const void*, size_t),
			t_rostr delim)
{
	return ft_lst_njoin(list, get_str, delim, INT_MAX);
}
