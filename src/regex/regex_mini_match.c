#include "shell42_utils.h"
#include "libft.h"

t_bool			regex_mini_match(t_rostr patern, t_rostr str)
{
	regex_t	regex_patern;
	int		ret;
	t_bool	result;

	if ((ret = regcomp(&regex_patern, patern, REG_EXTENDED)) != 0)
		regex_proj_error(&regex_patern, ret, 1);
	ret = regexec(&regex_patern, str, 0, NULL, 0);

	if (ret == 0)
		result = TRUE;
	else if (ret == REG_NOMATCH)
		result = FALSE;
	else
	{
		regex_proj_error(&regex_patern, ret, 42);
		result = -1;
	}

	regfree(&regex_patern);
	return result;
}
