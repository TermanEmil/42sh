#include "shell42.h"

t_shdata	shdata_construct(void)
{
	t_shdata	result;

	ft_bzero(&result, sizeof(result));
	result.input = shinput_construct();
	result.running_a_process = FALSE;
	return (result);
}
