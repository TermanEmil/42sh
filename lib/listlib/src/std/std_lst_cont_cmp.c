#include "listlib.h"

/*
** Function of type: t_lst_cont_cmp
*/

t_bool		std_lst_cont_cmp(
				const void *t1, const void *t2, size_t s1, size_t s2)
{
	(void)s2;
	return ft_memcmp(t1, t2, s1) == 0;
}
