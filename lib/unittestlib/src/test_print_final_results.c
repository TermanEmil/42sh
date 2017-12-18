#include "unittest.h"

void	test_print_final_results(t_ltest_rs result)
{
	ft_printf("Successes: %d\n", result.successes);
	ft_printf("Fails: %d\n", result.fails);
	ft_printf("\tSegFaults: %d\n", result.seg_faults);
	ft_printf("\tCoreDump: %d\n", result.core_dump);
}
