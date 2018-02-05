#include "listlib.h"

/*
** There are some standard compare functions.
** If NULL is passed as cmp, the ft_memcmp will be used.
**
** Return:
**  - the index of the first match;
**  - -1 on error;
*/

int	ft_lst_indexof(
		const t_list *lst,
		const void *target,
		size_t target_size,
		t_lst_cont_cmp *cmp)
{
	int		i;

	if (cmp == NULL)
		cmp = (t_lst_cont_cmp*)&ft_memcmp;

	i = 0;
	while (lst)
	{
		if (cmp(target, lst->content, target_size, lst->content_size))
			return i;
		i++;
		LTONEXT(lst);
	}

	return -1;
}

