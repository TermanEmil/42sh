#include "shinput.h"

static inline size_t	count_total_needed_len(t_lst_inkey const *lst,
							size_t const delim_len)
{
	size_t	result;

	result = 0;
	for (; lst; LTONEXT(lst))
	{
		if (lst->content == NULL)
			result += delim_len;
		else
		{
			result += ft_strlen(
				sh_inkey_get_pure_meaning(LCONT(lst, t_sh_inkey*)));
		}
	}
	return (result);
}

/*
** Gets the pure meaning of the given t_sh_inkey-s
*/

t_str					lst_in_key_get_pure_str(t_lst_inkey const *lst,
							t_rostr const delim)
{
	t_str	result;

	result = ft_strnew_raw(count_total_needed_len(lst, ft_strlen(delim)));
	if (result == NULL)
		ft_err_mem(1);

	for (; lst; LTONEXT(lst))
	{
		if (lst->content == NULL)
			ft_strcat(result, delim);
		else
		{
			ft_strcat(result,
				sh_inkey_get_pure_meaning(LCONT(lst, t_sh_inkey*)));
		}
	}

	return (result);
}
