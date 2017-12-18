#include "hashtablib.h"

t_hashpair const	g_htab_dummy = {{NULL, 0}, {NULL, 0}};

t_hashpair		*new_hashpair(t_hashmem const key, t_hashmem const val)
{
	static t_hashpair	result;

	result.key = key;
	result.val = val;
	return (&result);
}

t_hashpair		*new_hashpair_mllc(t_hashmem const key, t_hashmem const val)
{
	return (ft_memdup(new_hashpair(key, val), sizeof(t_hashpair)));
}
