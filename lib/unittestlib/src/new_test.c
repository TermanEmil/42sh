#include "unittest.h"

t_unittest *new_test(func_utest *test, char const *out, char const *f_name)
{
	static t_unittest result;

	result.f = test;
	result.expected_out = out;
	result.f_name = f_name;
	return (&result);
}
