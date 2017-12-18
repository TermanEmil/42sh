#include "shinput.h"

/*
** Returns the meaning part of a given key. If meaning is null, then it's the
** same as the displayable.
*/

char	*sh_inkey_get_meaning(t_sh_inkey const * const target)
{
	if (target == NULL)
		return (NULL);
	else if (target->meaning)
		return (target->meaning);
	else
		return (target->displayed_chars);
}
