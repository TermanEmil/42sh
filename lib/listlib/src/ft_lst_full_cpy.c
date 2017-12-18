#include "listlib.h"

/*
** Makes a copy of the given list copying its contents.
*/

t_list	*ft_lst_full_cpy(t_list const *head,
			t_lcpy_cont *cpy_f, t_ldel_func *del_f)
{
	t_list	*result;
	t_list	*aux;

	result = NULL;
	while (head)
	{
		aux = ft_lstnew(NULL, 0);
		if (aux == NULL)
		{
			ft_lstdel(&result, del_f);
			return (NULL);
		}
		aux->content = cpy_f(head->content, head->content_size);
		aux->content_size = head->content_size;
		ft_lstadd(&result, aux);
		LTONEXT(head);
	}
	return (result);
}
