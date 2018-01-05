#include "hashtablib.h"

/*
** Iterates through all the hashtab finding all instances which match the cmp_f.
** Give to cmp_f NULL to get all non null and non dummy pairs.
*/

t_hashpair	*htab_get_next_pair_iter(
				t_hashtab *htab,
				t_hashmem const key,
				ssize_t *last_i,
				t_cmp_f *cmp_f)
{
	t_hashpair	*pair;

	if (*last_i < 0)
		*last_i = 0;
	else
	{
		*last_i = (*last_i + 1) % htab->tablen;
		if (*last_i == 0)
			return (NULL);
	}
	pair = htab->tab[*last_i];
	if (pair != NULL && cmp_f == NULL && pair != &g_htab_dummy)
		return (pair);
	if (pair == NULL || pair == &g_htab_dummy ||
		cmp_f(pair->key.mem, key.mem, pair->key.size, key.size) != 0)
		return (htab_get_next_pair_iter(htab, key, last_i, cmp_f));
	return (pair);
}

