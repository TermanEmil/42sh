#include "shinput.h"

/*
** Returns the meaning of the key if it's a true char, else - an empty string.
*/

t_rostr	sh_inkey_get_pure_meaning(t_sh_inkey const * const key)
{
	if (key == NULL)
		return ("");
	else
		return (sh_inkey_get_meaning(key));
}
