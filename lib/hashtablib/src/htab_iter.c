#include "hashtablib.h"
#include "ft_errors.h"

/*
** Iterates through all buckets of the hashtab, applying the f function.
*/

void		htab_iter(t_hashtab * const htab, t_const_iter_f * const f)
{
	size_t	i;

	i = 0;
	while (i < htab->tablen)
	{
		f(htab->tab[i]);
		i++;
	}
}
