#include "eventlib.h"

void	event_add(t_hashtab * const events, char * const key,
			t_event_instance const event)
{
	t_hashpair		*pair;

	if (hashtab_load_factor(events) > 0.49f)
		htab_rehash(events, (events->tablen == 0) ? 1 : events->tablen);
	pair = new_hashpair_mllc(new_hashmem_str(key),
		new_hashmem_cp(&event, sizeof(event)));
	hashtab_add_pair(events, pair);
}
