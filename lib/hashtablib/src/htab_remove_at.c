#include "hashtablib.h"

/*
** After removal, a dummy value is placed instead of the removed bucket.
** https://youtu.be/EJOIt0KWFr4?t=2m23s
*/

ssize_t		htab_remove_at(t_hashtab * const hashtab, ssize_t const index)
{
	if (index < 0)
		return (index);
	del_hashpair(&hashtab->tab[index], hashtab->kdel, hashtab->vdel);
	hashtab->tab[index] = (t_hashpair*)&g_htab_dummy;
	return (index);
}
