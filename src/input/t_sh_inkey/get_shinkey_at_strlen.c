#include "shinput.h"

/*
** A lst of keys and a length is given. Using these, find the first key at which
** the length of the meaning so far is len. Normally, if we had no unicode, we
** could use ft_lstget(keys, len), but since the meaning of a key can have a len
** bigger than 1, this method is used instead.
** For len = 0, it will return the first key.
*/

t_lst_inkey		*get_shinkey_at_strlen(const t_lst_inkey *keys, int len)
{
	for (; keys; LTONEXT(keys))
	{
		if (len <= 0)
			return (t_lst_inkey*)keys;
		len -= ft_strlen(sh_inkey_get_meaning(LCONT(keys, t_sh_inkey*)));
	}
	return NULL;
}
