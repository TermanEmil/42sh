#include "hashtabtests.h"

void	add_hashpair_with_nulls(void)
{
	t_hashtab	*a;

	a = new_hashtab(1, NULL, NULL);
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem(NULL, 0),
			new_hashmem_str("C")));
	std_str_print_hashpair(get_hashpair(a, new_hashmem(NULL, 0)));
	del_hashtab(&a);
	FREE_TESTS();
}
