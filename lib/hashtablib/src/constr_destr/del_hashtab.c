#include "hashtablib.h"
#include "ft_errors.h"

void	del_hashtab(t_hashtab ** const tab)
{
	size_t	i;

	if (*tab == NULL)
		return;
	i = 0;
	while (i < (*tab)->tablen)
	{
		del_hashpair(&((*tab)->tab[i]), (*tab)->kdel, (*tab)->vdel);
		i++;
	}
	free((*tab)->tab);
	free(*tab);
	*tab = NULL;
}
