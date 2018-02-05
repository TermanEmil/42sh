#include "listlib.h"

static t_list	*rec_detach_(t_list **head, t_list *target, t_list *prev)
{
	t_list	*tmp;

	if (*head == NULL)
		return NULL;
	if (*head == target)
	{
		tmp = *head;
		if (prev == NULL)
		{
			LTONEXT(*head);
			if (*head)
				LPREV(*head) = NULL;
		}
		else
		{
			if (LNEXT(*head))
				LPREV(LNEXT(*head)) = prev;
			prev->next = LNEXT(*head);
		}
		return tmp;
	}
	else
		return rec_detach_(&LNEXT(*head), target, *head);
}

t_list			*ft_lst_detach(t_list **head, t_list *target)
{
	return rec_detach_(head, target, NULL);
}
