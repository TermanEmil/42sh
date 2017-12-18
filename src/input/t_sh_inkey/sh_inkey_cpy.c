#include "shinput.h"

static inline int	cpy_displayed_chars(t_sh_inkey const *target,
						t_sh_inkey * const result)
{
	if (target->displayed_chars)
	{
		result->displayed_chars = ft_strdup(target->displayed_chars);
		if (result->displayed_chars == NULL)
		{
			free(result);
			return (-1);
		}
	}
	else
		result->displayed_chars = NULL;
	if (target->meaning)
	{
		result->meaning = ft_strdup(target->meaning);
		if (result->meaning == NULL)
		{
			ft_memdel((void**)&result->displayed_chars);
			free(result);
			return (-1);
		}
	}
	else
		result->meaning = NULL;

	return (0);
}

t_sh_inkey		*sh_inkey_cpy(t_sh_inkey const *target)
{
	t_sh_inkey	*result;

	result = (t_sh_inkey*)malloc(sizeof(t_sh_inkey));
	if (result == NULL)
		ft_err_mem(1);

	if (cpy_displayed_chars(target, result) == -1)
		ft_err_mem(1);

	return (result);
}
