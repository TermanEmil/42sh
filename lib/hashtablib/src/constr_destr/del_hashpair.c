#include "hashtablib.h"

void	del_hashpair(t_hashpair ** const pair,
			t_del_mem_f * const kdel, t_del_mem_f * const vdel)
{
	if (*pair != NULL && *pair != (t_hashpair*)&g_htab_dummy)
	{
		if ((*pair)->key.mem != NULL && kdel != NULL)
			kdel((*pair)->key.mem, (*pair)->key.size);
		if ((*pair)->val.mem != NULL && vdel != NULL)
			vdel((*pair)->val.mem, (*pair)->val.size);
		free(*pair);
		*pair = NULL;
	}
}
