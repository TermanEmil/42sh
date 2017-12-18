#include "libft.h"

/*
** Adds str to dest from left.
** dest = ft_strnew(3);
** ft_str_stack_cat(dest, "1", 3);
** ft_str_stack_cat(dest, "2", 3);
** ft_str_stack_cat(dest, "3", 3);
** will make the dest to become "321"
** In case that there wasn't the third call, the dest would be "\021"
**
** Returns 0 when everything went find.
** Returns 1 if the dest is full
** Returns -1 if it failed.
*/

int		ft_str_stack_cat(char * const dest, char const * const str,
			size_t const dest_len)
{
	size_t	const str_len = ft_strlen(str);
	size_t	i;

	if (str_len > dest_len)
		return (-1);
	for (i = 0; i < dest_len; i++)
	{
		if (dest[i] != 0)
			break;
	}
	if (i == 0)
		return (-1);
	if (i > str_len)
	{
		ft_strncpy(dest + i - str_len, str, str_len);
		return (0);
	}
	else
	{
		ft_strncpy(dest, str + str_len - i, i);
		return (1);
	}
}
