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
