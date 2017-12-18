#include "hashtablib.h"

t_hashmem	new_hashmem(void * const mem, size_t const size)
{
	t_hashmem	result;

	result.mem = mem;
	result.size = size;
	return (result);
}

t_hashmem	new_hashmem_cp(void const *mem, size_t const size)
{
	if (mem == NULL)
		return (new_hashmem(NULL, size));
	else
		return (new_hashmem(ft_memdup(mem, size), size));
}
