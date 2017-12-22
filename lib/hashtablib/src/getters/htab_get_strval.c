#include "hashtablib.h"

t_str	htab_get_strval(const t_hashtab *htab, t_hashmem hashmem_key)
{
	return htab_get_val(htab, hashmem_key).mem;
}
