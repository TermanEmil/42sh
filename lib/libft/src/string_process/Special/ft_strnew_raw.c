#include "libft.h"

/*
** Create a fresh string, without initializing every byte to zero. Instead,
** initialize the first and the last byte with zero.
*/

t_str	ft_strnew_raw(size_t const len)
{
	t_str	result;

	result = (t_str)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[0] = 0;
	result[len] = 0;
	return (result);
}
