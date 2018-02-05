#include "listlib.h"

t_list		*ft_lst_min(const t_list *head, int (*cmp_get)(void*))
{
	int		min;
	int		lst_val;
	t_list	*next;
	t_list	*result;

	min = 0;
	result = NULL;
	for (; head; head = next)
	{
		next = LNEXT(head);
		lst_val = cmp_get(head->content);
		if (result == NULL || lst_val < min)
		{
			min = lst_val;
			result = (t_list*)head;
		}
	}
	return result;
}

void		*ft_lst_min_mem(const t_list *head, int (*cmp_get)(void*))
{
	t_list	*match;

	match = ft_lst_min(head, cmp_get);
	return (match == NULL) ? NULL : match->content;
}
