#include "shtests.h"

t_list	*g_tests;

int		main()
{
	char	buf[1024];

	g_tests = NULL;
	add_test(&g_tests,
		new_test(&memleak_1_shdisplay, "3", "memleak_1_shdisplay"));
	add_test(&g_tests,
		new_test(&memleak_1_shinput, "2 2", "memleak_1_shinput"));
	add_test(&g_tests, new_test(&shinput_seq_test_1,
			"^[^[aB \033\033aB\n4\n", "shinput_seq_test_1"));
	add_test(&g_tests, new_test(&input_history_test_add_pop,
			"0\n1\n2\n2\n3\ngH\neF\ncD\n", "input_history_test_add_pop"));
	test_print_final_results(run_listed_tests(g_tests, buf, sizeof(buf)));
	FREE_TESTS();
}