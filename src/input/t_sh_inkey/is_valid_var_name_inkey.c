#include "shinput.h"

/*
** Say if a given key is a valid char for a dollar var name.
*/

t_bool	is_valid_var_name_inkey(const t_sh_inkey *sh_inkey)
{
	t_rostr	meaning;

	if (sh_inkey == NULL)
		return FALSE;
	meaning = sh_inkey_get_meaning(sh_inkey);
	if (ft_strlen(meaning) != 1)
		return FALSE;
	return meaning[0] == '_' || ft_isalnum(meaning[0]);
}
