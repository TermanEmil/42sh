#include "eventlib.h"

/*
** Run the first occurance of the given event
*/

void	events_run_first(t_hashtab * const events, char const *key)
{
	if (events == NULL)
		return;
	
	t_hashpair const *pair = get_hashpair(events, new_hashmem_str((char*)key));

	if (pair)
		event_run(CAST(pair->val.mem, t_event_instance*));
}
