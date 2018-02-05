#include "listlib.h"

static t_bool	rec_rm_(
					t_list **head,
					const void *cont,
					t_lst_cont_cmp *cmp,
					t_list *prev,
					void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (*head == NULL)
		return FALSE;
	if (cmp(cont, (*head)->content, 0, (*head)->content_size))
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
		ft_lstdelone(&tmp, del);
		return TRUE;
	}
	else
		rec_rm_(&LNEXT(*head), cont, cmp, *head, del);
	return FALSE;
}

t_bool			ft_lstrm_cmp(
					t_list **h,
					const void* cont,
					t_lst_cont_cmp *cmp,
					t_ldel_func *del)
{
	return rec_rm_(h, cont, cmp, NULL, del);
}
