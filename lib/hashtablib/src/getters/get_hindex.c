#include "hashtablib.h"
#include "ft_errors.h"

/*
** Get hash index: returns the index at which the key would be placed
*/

size_t		get_hindex(t_hashtab const *htab, void const *key,
				size_t const ksize)
{
	if (htab->hash_f == NULL)
		ft_fatal("Hash function hasn't been set");
	if (htab->tablen == 0)
		ft_fatal("Hash tablen is zero");
	return (htab->hash_f(key, ksize) % htab->tablen);
}
