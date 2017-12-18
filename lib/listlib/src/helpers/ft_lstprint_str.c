#include "listlib.h"

void			ft_lstprint_str(t_list const * elem)
{
	if (elem)
		ft_putendl(LSTR(elem));
}