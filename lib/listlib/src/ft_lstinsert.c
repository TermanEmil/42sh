#include "listlib.h"

int		ft_lstinsert(t_list ** const head, size_t const i,
			t_list * const target, t_list * const prev)
{
	if (*head == NULL)
	{
		if (i != 0)
			return (-1);
		else
		{
			*head = target;
			if (prev)
				prev->next = *head;
			LPREV(target) = prev;
			return (0);
		}
	}
	if (i == 0)
	{
		LPREV(*head) = target;
		target->next = *head;
		if (prev)
			prev->next = target;
		else
			*head = target;
		LPREV(target) = prev;
		return (0);
	}
	return (ft_lstinsert(&LNEXT(*head), i - 1, target, *head));
}
