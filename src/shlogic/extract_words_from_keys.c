#include "shlogic.h"

/*
** Return a list of words, that is, a list of lists of keys.
** The first key of the first word would be:
** (*LCONT((*LCONT(words, t_list**)), t_sh_inkey**)
*/

t_lst_words	*extract_words_from_keys(t_lst_inkey const *keys)
{
	t_lst_words			*words;
	t_lst_inkey			*word_buf;
	t_rostr				key;
	t_sh_inkey			*inkey;

	words = NULL;
	word_buf = NULL;
	for (; keys; LTONEXT(keys))
	{
		inkey = LCONT(keys, t_sh_inkey*);	
		if (inkey == NULL ||
			(ft_strstr(" \t", (key = sh_inkey_get_meaning(inkey))) &&
			(ft_strchr("'\"\\`", inkey->inside_of) == NULL)))
		{
			if (word_buf != NULL)
				ft_lstadd(&words, ft_lstnew(&word_buf, sizeof(word_buf)));
			word_buf = NULL;
		}
		else
			ft_lstadd(&word_buf, ft_lstnew(&inkey, sizeof(inkey)));
	}

	if (word_buf != NULL)
		ft_lstadd(&words, ft_lstnew(&word_buf, sizeof(word_buf)));
	return words;
}
