#include "listlib.h"

static inline int	process_middle_insert(
						t_list **head,
						t_list * const elements)
{
	t_list	*last_elem;
	t_list	*prev;

	last_elem = ft_lst_get_last(elements);
	prev = LPREV(*head);
	LPREV(*head) = last_elem;
	LNEXT(last_elem) = *head;
	if (prev)
		prev->next = elements;
	else
		*head = elements;
	LPREV(elements) = prev;
	return (0);
}

int	ft_lst_insert_range(t_list **head, size_t const i, t_list * const elements)
{
	if (*head == NULL)
	{
		if (i != 0)
			return (-1);
		else
		{
			*head = elements;
			return (0);
		}
	}
	if (i == 0)
		return (process_middle_insert(head, elements));
	if (L_IS_LAST(*head) && i == 1)
	{
		LNEXT(*head) = elements;
		LPREV(elements) = *head;
		return (0);
	}
	return (ft_lst_insert_range(&LNEXT(*head), i - 1, elements));
}
