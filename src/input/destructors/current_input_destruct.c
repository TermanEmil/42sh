#include "shinput.h"

void			current_input_destruct(t_current_input * const target)
{
	if (target)
	{
		shinput_seq_destruct(target->input);
	}
}
