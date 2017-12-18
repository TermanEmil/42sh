#include "shlogic.h"

static void		lst_inkey_meaning_len(t_lst_inkey const *key,
					size_t * const len)
{
	*len += ft_strlen(sh_inkey_get_meaning(LCONT(key, t_sh_inkey*)));
}

static void		lst_inkey_concat_key(t_lst_inkey const *key, t_str buf)
{
	ft_strcat(buf, sh_inkey_get_meaning(LCONT(key, t_sh_inkey*)));
}

t_str			*lst_of_words_to_argv(t_lst_words const *lst_of_words)
{
	t_str	*result;
	size_t	len;
	int		i;

	len = 0;
	result = (t_str*)ft_memalloc(sizeof(t_str) * (ft_lstlen(lst_of_words) + 1));
	if (result == NULL)
		ft_err_mem(1);

	for (i = 0; lst_of_words; LTONEXT(lst_of_words), i++)
	{
		len = 0;
		ft_lstiter_arg_ptr(*LCONT(lst_of_words, t_lst_inkey**),
			(t_liter_arg_void*)&lst_inkey_meaning_len, &len);

		result[i] = ft_strnew_raw(len);
		if (result == NULL)
			ft_err_mem(1);

		ft_lstiter_arg_ptr(*LCONT(lst_of_words, t_lst_inkey**),
			(t_liter_arg_void*)&lst_inkey_concat_key, result[i]);
	}
	return (result);
}
