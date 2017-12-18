#include "hashtabtests.h"

/*
A: A
A: B
A: C
A: E
A: D

B: A
B: B

A: D
A: A
A: B
A: C
B: A
B: B
A: E
*/

static void	init_htab_a_with_some_random_vars(t_hashtab *a)
{
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("A"),
			new_hashmem_str("A")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("A"),
			new_hashmem_str("B")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("A"),
			new_hashmem_str("C")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("B"),
			new_hashmem_str("A")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("B"),
			new_hashmem_str("B")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("A"),
			new_hashmem_str("E")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("A"),
			new_hashmem_str("D")));
}

void	htab_get_next_pair_test(void)
{
	t_hashtab	*a;

	a = new_hashtab(7, NULL, NULL);
	init_htab_a_with_some_random_vars(a);

	ssize_t		last_i;
	ssize_t		start;
	t_hashpair	*tmp;

	last_i = -1;
	while ((tmp = htab_get_next_pair(a, new_hashmem_str("A"), &last_i, &start)))
	{
		std_str_print_hashpair(tmp);
	}

	ft_putnewl();

	start = -1;
	while ((tmp = htab_get_next_pair(a, new_hashmem_str("B"), &last_i, &start)))
	{
		std_str_print_hashpair(tmp);
	}

	ft_putnewl();
	htab_iter(a, &std_str_print_hashpair);

	del_hashtab(&a);
	FREE_TESTS();
}