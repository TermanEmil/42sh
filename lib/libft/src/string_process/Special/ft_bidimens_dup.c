#include "libft.h"

t_str		*ft_bidimens_dup(const t_str *tab)
{
	t_str	*result;
	int		i;

	result = ft_memalloc(sizeof(t_str) * (ft_tab_len((const void**)tab) + 1));
	if (result == NULL)
		return NULL;
	for (i = 0; tab[i]; i++)
	{
		result[i] = ft_strdup(tab[i]);
		if (result[i] == NULL)
		{
			ft_free_bidimens(result);
			return NULL;
		}
	}
	return result;
}
