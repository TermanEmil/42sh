#include "hashtablib.h"
#include "ft_errors.h"

/*
** Extends the hashtab with the given amount, creating a new hashtab->tab
** and reassigning all values.
*/

void		htab_rehash(t_hashtab * const htab, size_t const size_to_add)
{
	t_hashpair	**new_tab;
	t_hashpair	**old_tab;
	size_t		i;

	htab->tablen = size_to_add + htab->tablen;
	new_tab = (t_hashpair**)ft_memalloc(sizeof(t_hashpair*) * htab->tablen);
	if (new_tab == NULL)
		ft_err_mem(ERR_EXIT_PROG);
	old_tab = htab->tab;
	htab->tab = new_tab;
	htab->free_cells = htab->tablen;
	i = 0;
	while (i < htab->tablen - size_to_add)
	{
		if (old_tab[i] != (t_hashpair*)&g_htab_dummy)
			hashtab_add_pair(htab, old_tab[i]);
		i++;
	}
	free(old_tab);
}
