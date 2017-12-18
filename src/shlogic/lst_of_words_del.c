#include "shlogic.h"

void	lst_of_words_del(t_lst_words *lst_of_words)
{
	t_lst_words	*start;

	start = lst_of_words;
	while (lst_of_words)
	{
		ft_lstdel(LCONT(lst_of_words, t_lst_inkey**), NULL);
		LTONEXT(lst_of_words);
	}
	ft_lstdel(&start, &std_mem_del);
}
