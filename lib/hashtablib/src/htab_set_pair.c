#include "hashtablib.h"

/*
** Set the given pair. If the key doesn't exist, add the pair. If the key
** already exists, replace the value. A copy of the memory will be made.
*/

int				htab_set_pair(t_hashtab *htab, const t_hashpair *pair)
{
	t_hashpair	*tmp_pair;
	int			ret;

	tmp_pair = get_hashpair(htab, pair->key);
	if (tmp_pair == NULL)
	{
		ret = hashtab_add_pair(htab, new_hashpair_mllc(
			new_hashmem_cp(pair->key.mem, pair->key.size),
			new_hashmem_cp(pair->val.mem, pair->val.size)));
		if (ret != 0 || errno != 0)
			return -1;
	}
	else
	{
		if (tmp_pair->val.mem != NULL)
			free(tmp_pair->val.mem);
		tmp_pair->val = new_hashmem_cp(pair->val.mem, pair->val.size);
		if (errno != 0)
			return -1;
	}
	return 0;
}
