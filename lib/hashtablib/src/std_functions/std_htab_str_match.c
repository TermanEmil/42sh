#include "libft.h"

int		std_htab_str_match(char const *a, char const *b)
{

	if (a == NULL && b == NULL)
		return (0);
	else if (a == NULL || b == NULL)
		return (-1);
	return (!ft_match(a, b));
}
