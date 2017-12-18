#include "hashtabtests.h"

/*
** I have to free the unaccpeted memory.
** I just know that the first instance will be accepted for sure.
*/

void	not_enough_space_test(void)
{
	t_hashtab	*a;
	t_hashpair	*tmp;

	a = new_hashtab(1, &std_mem_del, &std_mem_del);
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("emil"),
			new_hashmem_str_cp("C")));
	tmp = new_hashpair_mllc(
			new_hashmem_str_cp("Valera"),
			new_hashmem_str_cp("Dasa"));
	if (hashtab_add_pair(a, tmp) == -1)
		del_hashpair(&tmp, &std_mem_del, &std_mem_del);
	tmp = new_hashpair_mllc(
			new_hashmem_str_cp("Sergiu"),
			new_hashmem_str_cp("Trafka"));
	hashtab_add_pair(a, tmp);
	if (hashtab_add_pair(a, tmp) == -1)
		del_hashpair(&tmp, &std_mem_del, &std_mem_del);
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("emil")));
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("Valera")));
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("Emil")));
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("Sergiu")));
	del_hashtab(&a);
	FREE_TESTS();
}
