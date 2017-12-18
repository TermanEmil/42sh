#include "listlib.h"

/*
** Not currently working with prev
*/

static int	lstrm_at_rec(t_list ** const head, size_t const index,
			t_ldel_func * const del, t_list * const prev)
{
	t_list	*tmp;

	if (*head == NULL)
		return (-1);
	if (index == 0)
	{
		tmp = *head;
		if (prev)
		{
			if (LNEXT(*head))
				LPREV(LNEXT(*head)) = prev;
			prev->next = LNEXT(*head);
		}
		else
		{
			LTONEXT(*head);
			if (*head)
				LPREV(*head) = NULL;
		}
		ft_lstdelone(&tmp, del);
		return (0);
	}
	else
		return (lstrm_at_rec(&LNEXT(*head), index - 1, del, *head));
}

int		ft_lstrm_at(t_list ** const head, size_t const index,
			t_ldel_func * const del)
{
	return (lstrm_at_rec(head, index, del, NULL));
}
