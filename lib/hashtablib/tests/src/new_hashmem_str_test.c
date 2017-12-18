#include "hashtabtests.h"

void	new_hashmem_str_test(void)
{
	t_hashmem	buf;

	buf = new_hashmem_str("a");
	ft_printf("%ld", buf.size);
	FREE_TESTS();
}
