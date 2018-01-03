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
	void	*cpy_mem;

	if (mem == NULL)
		return (new_hashmem(NULL, size));
	else
	{
		if ((cpy_mem = ft_memdup(mem, size)) == NULL)
			errno = ENOMEM;
		return (new_hashmem(cpy_mem, size));
	}
}
