#include "shell42.h"

t_shdata	shdata_construct(void)
{
	t_shdata	result;

	result.input = shinput_construct();
	return (result);
}
