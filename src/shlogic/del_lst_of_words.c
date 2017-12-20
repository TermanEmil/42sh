#include "shlogic.h"

static inline void	del_word_inside_lst(t_lst_inkey **keys)
{
	ft_lstdel(keys, &std_mem_del);
	free(keys);
}

/*
** Delete the words, without deleteing the keys inside.
*/

void				del_lst_of_words(t_lst_words *words)
{
	ft_lstdel(&words, (t_ldel_func*)&del_word_inside_lst);
}
