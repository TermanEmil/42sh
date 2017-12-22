#include "hashtablib.h"

t_hashmem htab_get_val(const t_hashtab *htab, t_hashmem hashmem_key)
{
	t_hashpair	*hashpair;

	hashpair = get_hashpair(htab, hashmem_key);
	if (hashpair == NULL)
		return new_hashmem(NULL, 0);
	else
		return hashpair->val;
}
