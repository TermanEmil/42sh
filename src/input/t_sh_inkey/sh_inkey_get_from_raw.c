#include "shinput.h"

/*
** Transforms a raw input to an `t_sh_inkey'
*/

t_sh_inkey				sh_inkey_get_from_raw(char const * const raw)
{
	char		buf[256];
	size_t		len;	
	size_t		i;
	char const	*disp_alternative;

	buf[0] = 0;
	for (i = 0; raw[i];)
	{
		disp_alternative = get_displayed_alternative(raw + i, &len);
		if (disp_alternative == NULL)
		{
			ft_strcat(buf, ft_char_to_str(raw[i]));
			i++;
		}
		else
		{
			ft_strcat(buf, disp_alternative);
			i += len;
		}
	}
	if (ft_strequ(raw, buf))
		return (sh_inkey_construct(ft_strdup(buf), NULL));
	return (sh_inkey_construct(ft_strdup(buf), ft_strdup(raw)));
}
