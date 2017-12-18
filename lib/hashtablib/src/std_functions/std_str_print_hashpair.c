#include "hashtablib.h"

/*
** Prints both key and val as strings
*/

void		std_str_print_hashpair(t_hashpair const *pair)
{
	if (pair != NULL)
	{
		if (pair == (t_hashpair*)&g_htab_dummy)
		{
			ft_putendl("Dummy");
			return;
		}
		ft_putstr((char*)(pair->key.mem));
		ft_putstr(": ");
		ft_putstr((char*)(pair->val.mem));
		ft_putnewl();
	}
}
