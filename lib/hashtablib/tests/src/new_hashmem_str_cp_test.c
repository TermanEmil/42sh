#include "hashtabtests.h"

void	new_hashmem_str_cp_test(void)
{
	t_hashmem	buf;

	buf = new_hashmem_str_cp("a");
	ft_printf("%ld", buf.size);
	free(buf.mem);
	FREE_TESTS();
}
