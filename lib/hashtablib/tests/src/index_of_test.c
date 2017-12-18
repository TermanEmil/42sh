#include "hashtabtests.h"

void	index_of_test(void)
{
	t_hashtab	*a;

	t_hashpair	*pair_2 = new_hashpair_mllc(
					new_hashmem_str("B"),
					new_hashmem_str("2"));

	t_hashpair	*pair_3 = new_hashpair_mllc(
					new_hashmem_str("B"),
					new_hashmem_str("3"));

	t_hashpair	*pair_4 = new_hashpair_mllc(
					new_hashmem_str("B"),
					new_hashmem_str("4"));

	a = new_hashtab(100, NULL, NULL);
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("A"),
			new_hashmem_str("1")));

	hashtab_add_pair(a, pair_2);
	hashtab_add_pair(a, pair_3);
	hashtab_add_pair(a, pair_4);

	ssize_t		last_i = -1;
	ssize_t		start;

	t_hashpair	*pair;
	ssize_t		index;

	pair = htab_get_next_pair(a, new_hashmem_str("B"), &last_i, &start);
	index = htab_index_of(a, pair);

	ft_printf("%d", a->tab[index] == pair_2);

	pair = htab_get_next_pair(a, new_hashmem_str("B"), &last_i, &start);
	index = htab_index_of(a, pair);

	ft_printf("%d", a->tab[index] == pair_3);

	pair = htab_get_next_pair(a, new_hashmem_str("B"), &last_i, &start);
	index = htab_index_of(a, pair);

	ft_printf("%d", a->tab[index] == pair_4);

	del_hashtab(&a);
	FREE_TESTS();
}
