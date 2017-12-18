#include "hashtabtests.h"

void	test_htab_cmp_f(void)
{
	t_hashtab	*a;
	ssize_t		last_i;
	ssize_t		start;
	t_hashpair	*pair_tmp;

	a = new_hashtab(100, NULL, NULL);
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("at_exit"),
			new_hashmem_str("A")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("at_exit_1"),
			new_hashmem_str("A")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("at_exit_2"),
			new_hashmem_str("A")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("at_exit_3"),
			new_hashmem_str("A")));

	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str("whatever"),
			new_hashmem_str("A")));

	last_i = -1;
	while ((pair_tmp = htab_get_next_pair_iter(a, new_hashmem_str("at_exit"),
		&last_i, (t_cmp_f*)&std_htab_str_match)))
	{
		std_str_print_hashpair(pair_tmp);
	}

	ft_putnewl();

	last_i = -1;
	while ((pair_tmp = htab_get_next_pair_iter(a, new_hashmem_str("at_exit*"),
		&last_i, (t_cmp_f*)&std_htab_str_match)))
	{
		std_str_print_hashpair(pair_tmp);
	}

	ft_putnewl();

	last_i = -1;
	while ((pair_tmp = htab_get_next_pair_iter(a, new_hashmem_str("at_exit_*"),
		&last_i, (t_cmp_f*)&std_htab_str_match)))
	{
		std_str_print_hashpair(pair_tmp);
	}

	ft_putnewl();

	last_i = -1;
	while ((pair_tmp = htab_get_next_pair_iter(a, new_hashmem_str("*"),
		&last_i, (t_cmp_f*)&std_htab_str_match)))
	{
		std_str_print_hashpair(pair_tmp);
	}

	del_hashtab(&a);
	FREE_TESTS();
}
