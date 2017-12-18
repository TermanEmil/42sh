#include "libft.h"

void	ft_strncpy_terminate(char * const dest, char const * const str,
			size_t const len)
{
	if (dest)
	{
		ft_strncpy(dest, str, len);
		dest[len] = 0;
	}
}
