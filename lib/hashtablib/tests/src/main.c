#include "hashtabtests.h"

#define REMOVAL_T_OUT "Dummy\nDummy\nDummy\nA: E\nC: C\n[Dummy]\n[Dummy]\n[Dummy]\n[A.]: [E.]\n[C.]: [C.]\nA: E\n\nDummy\n"
#define HTAB_GET_NEXT_PAIR_T_OUT "A: A\nA: B\nA: C\nA: E\nA: D\n\nB: A\nB: B\n\nA: D\nA: A\nA: B\nA: C\nB: A\nB: B\nA: E\n"
#define TEST_HTAB_CMP_F_OUT "at_exit: A\n\nat_exit_3: A\nat_exit_1: A\nat_exit_2: A\nat_exit: A\n\nat_exit_3: A\nat_exit_1: A\nat_exit_2: A\n\nat_exit_3: A\nat_exit_1: A\nat_exit_2: A\nwhatever: A\nat_exit: A\n"

t_list	*g_tests;

int		main()
{
	char	buf[1024];

	add_test(&g_tests, new_test(&basic_test, "emil: C\nValera: Dasa\n"
		"Sergiu: Trafka\n", "basic_test"));
	add_test(&g_tests, new_test(&new_hashmem_str_test,
		"2", "new_hashmem_str_test"));
	add_test(&g_tests, new_test(&new_hashmem_str_cp_test,
		"2", "new_hashmem_str_cp_test"));
	add_test(&g_tests, new_test(&not_enough_space_test,
		"emil: C\n", "not_enough_space_test"));
	add_test(&g_tests, new_test(&exceptional_test,
		"", "exceptional_test"));
	add_test(&g_tests, new_test(&add_hashpair_with_nulls,
		": C\n", "add_hashpair_with_nulls"));
	add_test(&g_tests, new_test(&removal_test,
		REMOVAL_T_OUT, "removal_test"));
	add_test(&g_tests, new_test(&htab_get_next_pair_test,
		HTAB_GET_NEXT_PAIR_T_OUT, "htab_get_next_pair_test"));
	add_test(&g_tests, new_test(&test_htab_cmp_f,
		TEST_HTAB_CMP_F_OUT, "test_htab_cmp_f"));
	add_test(&g_tests, new_test(&index_of_test,
		"111", "index_of_test"));
	test_print_final_results(run_listed_tests(g_tests, buf, sizeof(buf)));
	FREE_TESTS();
	return (0);
}
