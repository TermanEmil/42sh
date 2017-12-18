#include "libft.h"

void	ft_print_key(char const *str)
{
	while (*str)
	{
		if (ft_isprint(*str))
			ft_printf("%c ", *str);
		else
			ft_printf("%d ", *str);
		str++;
	}
	ft_putnewl();
}
