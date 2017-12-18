#include "libft.h"

int		std_htab_mem_cmp(void const *a, void const *b,
			size_t const asize, size_t const bsize)
{
	if (a == NULL && b == NULL)
		return (0);
	else if (a == NULL || b == NULL)
		return (-1);
	return (!(asize == bsize && ft_memcmp(a, b, asize) == 0));
}