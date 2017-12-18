#include "eventlibtests.h"
#include "unittest.h"

t_list	*g_tests;

void	test_g_events(void)
{
	events_init_globals(0);
	event_add(g_events, "at_exit", event_instance_construct(
		(t_handler_f*)&ft_putendl, "Exiting"));
	FREE_TESTS();
	event_exit(0);
}

int		main(void)
{
	char	buf[1024];

	g_tests = NULL;

	add_test(&g_tests, new_test(&general_test,
		"[event1]: 4\n[event1]: 1\n[event1]: 3\n[event1]: 2\n", "general_test"));
	add_test(&g_tests, new_test(&remove_add_test,
		"[event1]: 4\nrolling2\n[event1]: 2\n[event1]: 3\n", "remove_add_test"));
	add_test(&g_tests, new_test(&test_g_events,
		"Exiting\n", "test_g_events"));

	test_print_final_results(run_listed_tests(g_tests, buf, sizeof(buf)));

	FREE_TESTS();
	return (0);
}