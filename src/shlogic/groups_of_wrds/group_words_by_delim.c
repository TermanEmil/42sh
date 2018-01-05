#include "shlogic.h"

/*
** Group words when a word is equal to the given delimiter.
*/

t_grps_wrds	*group_words_by_delim(t_lst_words *words, t_rostr delim)
{
	t_lst_words	*buf;
	t_list		*result;
	t_str		argv;

	buf = NULL;
	result = NULL;
	for (; words; LTONEXT(words))
	{
		argv = word_to_str(LCONT(words, t_lst_inkey*));
		if (argv == NULL)
			ft_err_mem(1);
		if (ft_strequ(argv, delim))
		{
			if (buf != NULL)
				ft_lstadd(&result, ft_lstnew_nocpy(buf, sizeof(buf)));
			buf = NULL;
		}
		else
			ft_lstadd(&buf, ft_lstnew_nocpy(
				LCONT(words, t_lst_inkey*), sizeof(t_lst_inkey*)));
		free(argv);
	}
	if (buf != NULL)
		ft_lstadd(&result, ft_lstnew_nocpy(buf, sizeof(buf)));
	return result;
}
