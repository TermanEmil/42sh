#include "listlib.h"

static t_list*	ft_lstget_prevof_last(t_list * head)
{
	if (head == NULL || L_IS_LAST(head))
		return NULL;
	if (L_IS_LAST(head->next))
		return head;
	else
		return ft_lstget_prevof_last(LNEXT(head));
}

void	ft_lstpop_back(t_list ** head, t_ldel_func * del)
{
	t_list * tmp;

	if (*head == NULL)
		return;
	if (L_IS_LAST(*head))
		ft_lstdelone(head, del);
	else
	{
		tmp = ft_lstget_prevof_last(*head);
		ft_lstdelone(&LNEXT(tmp), del);
		LNEXT(tmp) = NULL;
	}
}