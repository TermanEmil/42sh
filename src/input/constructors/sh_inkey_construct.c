#include "shinput.h"
#include "ft_colors.h"

t_sh_inkey	sh_inkey_construct(char * const displayed_chars,
				char * const meaning)
{
	t_sh_inkey	result;

	ft_bzero(&result, sizeof(result));
	result.displayed_chars = displayed_chars;
	result.meaning = meaning;
	if (displayed_chars == NULL)
		ft_err(C_CYAN "Warning in sh_inkey_construct: "
			"displayed_chars can't be NULL" C_EOC);
	return (result);
}

t_sh_inkey	sh_inkey_cpy_construct(const t_sh_inkey *target)
{
	t_sh_inkey	result;

	ft_memcpy(&result, target, sizeof(t_sh_inkey));
	if (target->displayed_chars != NULL)
		result.displayed_chars = ft_strdup(target->displayed_chars);
	if (target->meaning != NULL)
		result.meaning = ft_strdup(target->meaning);
	return result;
}

t_sh_inkey	*sh_inkey_cpy_construct_ptr(const t_sh_inkey *target)
{
	t_sh_inkey	tmp;

	tmp = sh_inkey_cpy_construct(target);
	return ft_memdup(&tmp, sizeof(tmp));
}