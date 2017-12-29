#include "listlib.h"

/*
** Make a copy of the given range. To make a full copy, it could be used:
** ft_lst_cpy_range(lst, 0, INT_MAX, &some_cpy_f);
*/

t_list		*ft_lst_cpy_range(
				const t_list *head, int i1, int i2,
				t_lcpy_cont *f_cpy_cont)
{
	t_list	*result;

	if (i1 > i2 || i1 < 0 || i2 < 0)
		return NULL;
	while (i1 != 0 && head)
	{
		i1--;
		i2--;
		LTONEXT(head);
	}
	result = NULL;
	while (head && i2 >= 0)
	{
		i2--;
		ft_lstadd(&result, ft_lstnew_nocpy(
			f_cpy_cont(head->content, head->content_size),
			head->content_size));
		LTONEXT(head);
	}
	return result;
}
