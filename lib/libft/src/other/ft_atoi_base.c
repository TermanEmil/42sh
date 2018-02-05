#include "libft.h"

int		ft_atoi_base(t_rostr str, int base)
{
	int	result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * base + *str - '0';
		str++;
	}
	return result;
}
