#include "shlogic.h"

/*
** Extract the meaning of the given keys into a fresh string, with specific
** delimiters. It's used, for example, to detect the string key of dollar
** var.
*/

t_str	extract_var_name_from_keys(const t_lst_inkey *keys)
{
	const t_sh_inkey	*sh_inkey;
	const t_lst_inkey	*start;
	int					count;

	start = keys;	
	for (count = 0; keys; LTONEXT(keys), count++)
	{
		sh_inkey = LCONT(keys, t_sh_inkey*);
		if (sh_inkey == NULL)
			break;
		if (!is_valid_var_name_inkey(sh_inkey))
			break;
	}

	return ft_lst_njoin(
		start,
		(t_rostr (*)(const void*, size_t))&sh_inkey_get_meaning, NULL, count);
}
