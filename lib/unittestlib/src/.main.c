#include "unittest.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "ft_errors.h"
#include "ft_colors.h"

void random_test(void)
{

	ft_putstr("emil");
	// ft_putstr("hey");

	// ft_putstr_fd("stderr\n", 2);
}

//todo: expected_out expted_err
int		main()
{
	char	buf[124];
	t_list *tests;

	tests = NULL;
	
	add_test(&tests, new_test(&random_test, "emil", "random_test"));
	add_test(&tests, new_test(&random_test, "emil", "random_test"));
	add_test(&tests, new_test(&random_test, "emil", "random_test"));

	test_print_final_results(run_listed_tests(tests, buf, sizeof(buf)));
	return (0);
}