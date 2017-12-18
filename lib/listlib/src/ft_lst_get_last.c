#include "listlib.h"

t_list	*ft_lst_get_last(t_list * const head)
{
	if (head == NULL)
		return (NULL);
	if (L_IS_LAST(head))
		return (head);
	return (ft_lst_get_last(LNEXT(head)));
}
