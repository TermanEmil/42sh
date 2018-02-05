#include "listlib.h"

void			ft_lstiter_mem(t_list *lst, void (*f)(void *content))
{
	t_list	*next;

	for (; lst; lst = next)
	{
		next = LNEXT(lst);
		f(lst->content);
	}
}
