#include "listlib.h"

void		ft_lstiter_mem2(
				t_list *lst,
				void *data,
				void (*f)(void *data, void *cont))
{
	t_list	*next;

	while (lst)
	{
		next = LNEXT(lst);
		f(data, lst->content);
		lst = next;
	}
}
