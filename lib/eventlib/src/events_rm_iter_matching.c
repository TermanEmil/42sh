#include "eventlib.h"

void		events_rm_iter_matching(t_hashtab * const events,
				char const *key, t_cmp_f *cmp_f)
{
	ssize_t				last_i;
	ssize_t				index;
	t_hashpair			*pair_tmp;
	t_hashmem const		key_hm = new_hashmem_str((char*)key);

	if (events == NULL)
		return;
	last_i = -1;
	while ((pair_tmp = htab_get_next_pair_iter(events, key_hm, &last_i, cmp_f)))
	{
		index = htab_index_of(events, pair_tmp);
		htab_remove_at(events, index);
	}
}
