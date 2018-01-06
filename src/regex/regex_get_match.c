#include "regex_tools.h"
#include "libft.h"
#include "ft_errors.h"

/*
** Make a fresh string with the first match.
*/

t_str			regex_get_match(t_rostr patern, t_rostr str)
{
	regmatch_t	pmatch;
	int			match_len;
	t_str		result;

	pmatch = regex_mini_get_regmatch(patern, str);

	if (pmatch.rm_so == -1)
		return NULL;

	match_len = pmatch.rm_eo - pmatch.rm_so;
	result = ft_strndup(str + pmatch.rm_so,  match_len);
	if (result == NULL)
		ft_err_mem(TRUE);
	return result;
}
