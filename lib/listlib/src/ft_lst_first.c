#include "listlib.h"

t_list	*ft_lst_first(
			const t_list *lst,
			const void *target,
			size_t target_size,
			t_lst_cont_cmp *cmp)
{
	if (cmp == NULL)
		cmp = (t_lst_cont_cmp*)&ft_memcmp;

	while (lst)
	{
		if (cmp(target, lst->content, target_size, lst->content_size))
			return (t_list*)lst;
		LTONEXT(lst);
	}

	return NULL;
}
