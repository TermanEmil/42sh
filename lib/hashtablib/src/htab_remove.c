#include "hashtablib.h"

ssize_t		htab_remove(t_hashtab * const hashtab, t_hashmem const key)
{
	return (htab_remove_at(hashtab, get_key_index(hashtab, key, FALSE)));
}
