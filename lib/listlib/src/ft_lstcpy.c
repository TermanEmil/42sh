#include "listlib.h"

/*
** Makes a copy of the given list without copying its contents.
*/

t_list	*ft_lstcpy(t_list const *head)
{
	t_list	*result;
	t_list	*aux;

	result = NULL;
	while (head)
	{
		aux = ft_lstcpy_one(head);
		if (aux == NULL)
		{
			ft_lstdel(&result, NULL);
			return (NULL);
		}
		ft_lstadd(&result, aux);
		LTONEXT(head);
	}
	return (result);
}
