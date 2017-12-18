#include "listlib.h"

void	ft_lst_rev_iter(t_list *lst, void (*f)(t_list *elem))
{
	while (lst)
	{
		f(lst);
		lst = lst->prev;
	}
}
