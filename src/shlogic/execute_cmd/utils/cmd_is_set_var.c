#include "shlogic.h"
#include <regex.h>

/*
** Check if the given string is a valid shell set var: MY_VAR=anything
*/

t_bool	cmd_is_set_var(t_rostr str)
{
	int			ret;
	regex_t		regex_patern;

	if ((ret = regcomp(&regex_patern, "[a-z0-9_]+=.*", REG_ICASE | REG_EXTENDED)) != 0)
		ft_proj_err("Regex failed at cmd_is_set_var (1)", 1);
	
	ret = regexec(&regex_patern, str, 0, NULL, 0);
	regfree(&regex_patern);

	if (ret == 0)
		return TRUE;
	if (ret == REG_NOMATCH)
		return FALSE;
	else
		ft_proj_err("Regex failed at cmd_is_set_var (2)", 1);
	return -1;
}
