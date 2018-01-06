#include "regex_tools.h"
#include "libft.h"

/*
** Tell if there is at least one match.
*/

t_bool			regex_mini_match(t_rostr patern, t_rostr str)
{
	regmatch_t	pmatch;

	pmatch = regex_mini_get_regmatch(patern, str);
	return pmatch.rm_so != -1;
}
