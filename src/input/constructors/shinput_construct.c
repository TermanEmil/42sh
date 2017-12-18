#include "shinput.h"

t_shinput	shinput_construct(void)
{
	t_shinput	result;

	result.current = current_input_construct();
	result.history = input_history_construct();
	return (result);
}
