#include "listlib.h"

t_list	*ft_lstnew_nocpy(void *content, size_t content_size)
{
	t_list	*result;

	result = (t_list*)malloc(sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	result->prev = NULL;
	if (content == NULL)
	{
		result->content = NULL;
		result->content_size = 0;
	}
	else
	{
		result->content = content;
		result->content_size = content_size;
	}
	return (result);	
}

t_list	*ft_lstnew_str_nocpy(char *str)
{
	return ft_lstnew_nocpy(str, (str == NULL) ? 0 : ft_strlen(str));
}
