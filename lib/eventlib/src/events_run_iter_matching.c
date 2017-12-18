#include "eventlib.h"

/*
** With this you can run events with wildcards, like 'exit_at_*'
*/

void	events_run_iter_matching(t_hashtab * const events,
				char const *key, t_cmp_f *cmp_f)
{
	ssize_t				last_i;
	t_hashpair			*pair_tmp;
	t_hashmem const		key_hm = new_hashmem_str((char*)key);

	if (events == NULL)
		return;
	last_i = -1;
	while ((pair_tmp = htab_get_next_pair_iter(events, key_hm, &last_i, cmp_f)))
		event_run(CAST(pair_tmp->val.mem, t_event_instance*));
}
