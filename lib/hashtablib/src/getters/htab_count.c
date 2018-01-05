#include "hashtablib.h"

int		htab_count(const t_hashtab *htab)
{
	return htab->tablen - htab->free_cells;
}
