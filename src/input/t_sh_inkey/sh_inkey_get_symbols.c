#include "shinput.h"

/*
** Returns the number of symbols the given key->displayed_chars has
*/

size_t	sh_inkey_get_symbols(t_sh_inkey const * const key)
{
	if (char_is_utf8((t_uchar*)key->displayed_chars))
		return (1);
	else
		return (ft_strlen(key->displayed_chars));
}
