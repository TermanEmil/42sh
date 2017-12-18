#include "shinput.h"

t_bool	sh_inkey_is_delim(t_sh_inkey const * const key)
{
	int			i;
	char const	* const meaning = sh_inkey_get_meaning(key);

	if (ft_strlen(meaning) != 1)
		return (FALSE);
	for (i = 0; SHELL_INPUT_DELIMS[i]; i++)
	{
		if (meaning[0] == SHELL_INPUT_DELIMS[i])
			return (TRUE);
	}
	return (FALSE);
}
