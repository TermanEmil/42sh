#include "libft.h"

t_bool	ft_str_is_numb(t_rostr str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return FALSE;
		str++;
	}
	return TRUE;
}
