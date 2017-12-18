#include "hashtablib.h"
#include "ft_errors.h"

/*
** Get key index: returns the index at which the key is located in the
** htab using the linear probing method
*/

ssize_t		get_key_index(t_hashtab const *htab,
				t_hashmem const key, int const search_free_cell)
{
	if (htab->hashcol_f == NULL)
		ft_fatal("Hashcol_f function hasn't been set");
	return (htab->hashcol_f(htab, key.mem, key.size, search_free_cell));
}
