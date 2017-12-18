#include "listlib.h"

/*
** Makes a new list node out of the first element of the given list, without
** copying compying the content, but assigning a reference to it.
*/

t_list	*ft_lstcpy_one(t_list const *head)
{
	t_list	*result;

	if (head == NULL)
		return (NULL);

	result = ft_lstnew(NULL, 0);
	if (result == NULL)
		return (NULL);
	
	result->content = head->content;
	result->content_size = head->content_size;
	return (result);
}
