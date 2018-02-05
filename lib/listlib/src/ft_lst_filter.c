#include "listlib.h"

/*
** Create a list with the contents from the lst, without actually copying the
** content.
*/

t_list			*ft_lst_filter(
					t_list *lst,
					const void *cmp_data,
					size_t data_size,
					t_lst_cont_cmp *cmp)
{
	t_list	*result;

	result = NULL;
	for (; lst; LTONEXT(lst))
	{
		if (cmp(cmp_data, lst->content, data_size, lst->content_size))
		{
			ft_lstadd(&result,
				ft_lstnew_nocpy(lst->content, lst->content_size));
		}
	}
	return result;
}
