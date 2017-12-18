#include "shinput.h"

/*
** An array of string pairs, which represent the visual value of different
** string combinations.
** It must have the same number of symbols.
*/

static t_str_pair const	g_disp_alternatives[10] = {
							{"\033", "↯"},
							{NULL, NULL}};

/*
** Tries to find any combination from the array above at the beginning of the
** given string. If it finds a combination, the visual value is returned and
** len gets the length of the 'replaced' string.
** for {"\033", "^"}: return "^", len = ft_strlen("\033")
*/

char const		*get_displayed_alternative(char const * const str,
							size_t * const len)
{
	int		i;
	size_t	tmp;

	for (i = 0; g_disp_alternatives[i].first != NULL; i++)
	{
		tmp = ft_strlen(g_disp_alternatives[i].first);
		if (ft_strlen(str) == tmp &&
			ft_strnequ(str, g_disp_alternatives[i].first, tmp))
		{
			if (len)
				*len = tmp;
			return (g_disp_alternatives[i].second);
		}
	}
	if (len)
		*len = 0;
	return (NULL);
}
