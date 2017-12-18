#include "hashtablib.h"

ssize_t	hash_linear_probing_method(t_hashtab const *htab,
			void const *key, size_t const ksize, int const search_free_cell)
{
	size_t		result;
	size_t		starting_point;
	t_hashpair	*pair;

	starting_point = get_hindex(htab, key, ksize);
	result = starting_point;
	while (htab->tab[result] != NULL)
	{
		pair = htab->tab[result];
		if (!search_free_cell)
		{
			if (htab->cmp_f(pair->key.mem, key, pair->key.size, ksize) == 0)
				return (result);
		}
		result = (result + 1) % htab->tablen;
		if (result == starting_point)
			return (-1);
	}
	if (!search_free_cell && htab->tab[result] == NULL)
		result = -1;
	return (result);
}
