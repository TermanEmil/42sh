#include "shlogic.h"

static void		del_word_inside_lst(t_lst_inkey *keys)
{
	ft_lstdel(&keys, (t_ldel_func*)&sh_inkey_destruct);
}

static void		del_word_lst_not_content(t_lst_inkey *keys)
{
	ft_lstdel(&keys, NULL);
}

/*
** Delete the words, without deleteing the keys inside.
*/

void			del_lst_of_words(t_lst_words *words)
{
	ft_lstdel(&words, (t_ldel_func*)&del_word_inside_lst);
}

/*
** Delete a lst of words without deleting its content. Delete only the lst
** structure.
*/

void			del_lst_of_words_not_content(t_lst_words *words)
{
	ft_lstdel(&words, (t_ldel_func*)&del_word_lst_not_content);
}