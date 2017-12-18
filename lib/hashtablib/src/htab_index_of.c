#include "hashtablib.h"

/*
** Returns the index of the pair in the htab
*/

ssize_t		htab_index_of(t_hashtab const *htab, t_hashpair const *pair)
{
	ssize_t		result;
	ssize_t		starting_point;

	if (htab == NULL || pair == NULL)
		return (-1);
	starting_point = get_key_index(htab, pair->key, FALSE);
	result = starting_point;
	if (result < 0)
		return (-1);
	while (htab->tab[result] != NULL)
	{
		if (htab->tab[result] == pair)
			return (result);
		result = (result + 1) % htab->tablen;
		if (result == starting_point)
			return (-1);
	}
	return (-1);
}
