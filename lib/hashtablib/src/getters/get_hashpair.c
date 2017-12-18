#include "hashtablib.h"
#include "ft_errors.h"

/*
** Returns the pair from the hashtab, if there is one.
** Doesn't handle any exceptions.
*/

t_hashpair	*get_hashpair(t_hashtab const *htab, t_hashmem const key)
{
	ssize_t	index;

	if (htab == NULL || htab->tab == NULL || htab->tablen == 0)
		return (NULL);
	index = get_key_index(htab, key, 0);
	if (index == -1)
		return (NULL);
	else
		return (htab->tab[index]);
}
