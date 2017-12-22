#include "shinput.h"

/*
** Transform each char of the given string into a lst of t_sh_inkey-s.
*/

t_lst_inkey		*get_sh_inkeys_from_str(t_rostr str)
{
	t_lst_inkey	*lst_keys;
	t_sh_inkey	sh_inkey;

	lst_keys = NULL;
	for (; *str; str++)
	{
		sh_inkey = sh_inkey_construct(ft_strdup(ft_char_to_str(*str)), NULL);
		ft_lstadd(&lst_keys, ft_lstnew(&sh_inkey, sizeof(sh_inkey)));
	}
	return lst_keys;
}
