#include "libft.h"

/*
** Substitute inside str from start to end with needle, realocating the memory.
*/

void			ft_str_mlc_sub(t_str *str, t_rostr needle, int start, int end)
{
	t_str	tmp;

	if (*str == NULL)
	{
		*str = ft_strdup(needle);
		return;
	}
	(*str)[start] = '\0';
	tmp = ft_strmegajoin(3, *str, needle, (*str) + end);
	free(*str);
	*str = tmp;
}
