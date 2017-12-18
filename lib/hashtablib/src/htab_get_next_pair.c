#include "hashtablib.h"

/*
** Returns the next hpair with the same key.
** Useful when trying to get all pairs with the same key.
** If last_i or start is negative, it searches for the key index.
**
** See the `htab_get_next_pair_test' to better understand
*/

t_hashpair	*htab_get_next_pair(t_hashtab * const htab, t_hashmem const key,
				ssize_t * const last_i, ssize_t * const start)
{
	t_hashpair	*pair;

	if (*last_i < 0 || *start < 0)
	{
		*start = get_key_index(htab, key, !HTAB_SEARCHING_FOR_FREE_CELL);
		*last_i = *start;
		if (*start < 0)
			return (NULL);
		return (htab->tab[*last_i]);
	}
	*last_i = (*last_i + 1) % htab->tablen;
	pair = htab->tab[*last_i];
	if (*last_i == *start || pair == NULL)
		return (NULL);
	if (htab->cmp_f(pair->key.mem, key.mem, pair->key.size, key.size) != 0)
		return (htab_get_next_pair(htab, key, last_i, start));
	return (pair);
}
