#include "shinput.h"

/*
** Transform the given string into a list of sh_inkeys.
*/

t_lst_inkey		*get_sh_inkeys_from_str(t_rostr str)
{
	t_lst_inkey	*lst_keys;
	t_sh_inkey	sh_inkey;
	t_rostr		utf8_char;

	lst_keys = NULL;
	while (*str)
	{
		utf8_char = utf8_get_first((const unsigned char*)str);
		sh_inkey = sh_inkey_construct(ft_strdup(utf8_char), NULL);
		ft_lstadd(&lst_keys, ft_lstnew(&sh_inkey, sizeof(sh_inkey)));
		str += ft_strlen(utf8_char);
	}
	return lst_keys;
}
