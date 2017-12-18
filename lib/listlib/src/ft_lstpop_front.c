#include "listlib.h"

void	ft_lstpop_front(t_list ** head, t_ldel_func * del)
{
	t_list * tmp;

	if (*head == NULL)
		return;
	tmp = *head;
	*head = LNEXT(*head);
	LPREV(*head) = NULL;
	ft_lstdelone(&tmp, del);
}