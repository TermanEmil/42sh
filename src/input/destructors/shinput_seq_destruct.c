#include "shinput.h"

void			shinput_seq_destruct(t_shinput_seq * const target)
{
	if (target)
	{
		ft_lstdel(&target->keys, (t_ldel_func*)&sh_inkey_destruct);
		free(target);
	}
}
