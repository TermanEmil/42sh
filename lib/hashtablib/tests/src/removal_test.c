#include "hashtabtests.h"

void	removal_test(void)
{
	t_hashtab	*a;

	a = new_hashtab(100, &std_mem_del, &std_mem_del);
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("A"),
			new_hashmem_str_cp("A")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("A"),
			new_hashmem_str_cp("B")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("A"),
			new_hashmem_str_cp("D")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("C"),
			new_hashmem_str_cp("C")));
	htab_remove(a, new_hashmem_str("A"));
	htab_remove(a, new_hashmem_str("A"));
	htab_remove(a, new_hashmem_str("A"));
	htab_remove(a, new_hashmem_str("A"));
	htab_remove(a, new_hashmem_str("A"));
	htab_remove(a, new_hashmem_str("A"));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("A"),
			new_hashmem_str_cp("E")));
	htab_iter(a, &std_str_print_hashpair);
	htab_iter(a, &std_mem_print_hashpair);
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("A")));
	htab_remove(a, new_hashmem_str("A"));
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("A")));
	htab_rehash(a, 10);
	ft_putnewl();
	htab_remove(a, new_hashmem_str("C"));
	htab_iter(a, &std_str_print_hashpair);
	del_hashtab(&a);
	FREE_TESTS();
}