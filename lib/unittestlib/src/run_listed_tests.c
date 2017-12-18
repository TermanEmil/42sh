#include "unittest.h"
#include <sys/wait.h>

t_ltest_rs	run_listed_tests(t_list * tests, char * buf, ssize_t buf_len)
{
	t_ltest_rs	result;
	int			ret;

	ft_bzero(&result, sizeof(result));
	ft_bzero(buf, buf_len);
	while (tests)
	{
		ret = run_test(LTEST(tests), buf, buf_len);
		if (ret == TEST_SUCC)
			result.successes++;
		else
		{
			result.fails++;
			result.seg_faults += (ret == 139);
			result.core_dump += (ret == TEST_COREDUMP);
		}
		LTONEXT(tests);
	}
	return (result);
}
