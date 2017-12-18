#include "hashtabtests.h"

void	exceptional_test(void)
{
	t_hashtab	*a;

	a = NULL;
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("emil")));
	del_hashtab(&a);
	FREE_TESTS();
}
