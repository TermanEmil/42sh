#include "listlib.h"

t_list		*ft_lst_max(const t_list *head, int (*cmp_get)(void*))
{
	int		max;
	int		lst_val;
	t_list	*next;
	t_list	*result;

	max = 0;
	result = NULL;
	for (; head; head = next)
	{
		next = LNEXT(head);
		lst_val = cmp_get(head->content);
		if (result == NULL || lst_val > max)
		{
			max = lst_val;
			result = (t_list*)head;
		}
	}
	return result;
}

void		*ft_lst_max_mem(const t_list *head, int (*cmp_get)(void*))
{
	t_list	*match;

	match = ft_lst_max(head, cmp_get);
	return (match == NULL) ? NULL : match->content;
}
