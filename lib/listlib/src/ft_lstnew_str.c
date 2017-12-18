#include "listlib.h"

t_list	*ft_lstnew_str(char const * const str)
{
	return (ft_lstnew(str, ft_strlen(str) + 1));
}
