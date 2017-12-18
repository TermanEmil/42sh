#include "shinput.h"

void		sh_inkey_destruct(t_sh_inkey * const target)
{
	if (target)
	{
		if (target->displayed_chars)
			free(target->displayed_chars);
		if (target->meaning)
			free(target->meaning);
		free(target);
	}
}
