#include "eventlib.h"

void	events_run_all(t_hashtab * const events, char const *key)
{
	ssize_t				last_i;
	ssize_t				start;
	t_hashpair			*pair_tmp;

	if (events == NULL)
		return;
	last_i = -1;
	while ((pair_tmp = htab_get_next_pair(events,
		new_hashmem_str((char*)key), &last_i, &start)))
	{
		event_run(CAST(pair_tmp->val.mem, t_event_instance*));
	}
}
