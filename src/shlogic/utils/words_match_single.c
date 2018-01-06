#include "shlogic.h"

/*
** Check if the given words is of the size 1 and regex match the patern.
*/

t_bool	words_match_single(const t_lst_words *words, t_rostr patern)
{
	t_lst_inkey	*keys;

	if (words == NULL || ft_lstlen(words) != 1)
		return FALSE;

	keys = LCONT(words, t_lst_inkey*);
	return word_matches(keys, patern);
}
