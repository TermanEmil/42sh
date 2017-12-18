#include "hashtablib.h"

float		hashtab_load_factor(t_hashtab const *hashtab)
{
	if (hashtab->tablen == 0)
		return (1);
	return ((hashtab->tablen - hashtab->free_cells) / ((float)hashtab->tablen));
}