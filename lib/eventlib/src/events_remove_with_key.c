#include "eventlib.h"

void		events_remove_with_key(t_hashtab * const events, char const *key)
{
	while (htab_remove(events, new_hashmem_str((char*)key)) >= 0);
}
