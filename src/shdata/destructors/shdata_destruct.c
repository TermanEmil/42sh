#include "shell42.h"

void		shdata_destruct(t_shdata * const target)
{
	if (target)
	{
		shinput_destruct(&target->input);
	}
}
