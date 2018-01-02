 #include "shlogic.h"

static inline t_sh_inkey	*cpy_inkey(const t_sh_inkey *target)
{
	static t_sh_inkey	buf;

	buf = sh_inkey_cpy_construct(target);
	return &buf;
}

static inline void			add_word(t_lst_words **words, t_lst_inkey **word)
{
	if (*word != NULL)
	{
		ft_lstadd(words, ft_lstnew_nocpy(*word, sizeof(**word)));
		*word = NULL;
	}
}

/*
** Return a list of words, that is, a list of lists of keys.
** The first key of the first word would be:
** LCONT((LCONT(words, t_list*)), t_sh_inkey*)
*/

t_lst_words	*extract_words_from_keys(t_lst_inkey const *keys)
{
	t_lst_words			*words;
	t_lst_inkey			*word_buf;
	t_rostr				key;
	const t_sh_inkey	*inkey;

	words = NULL;
	word_buf = NULL;
	for (; keys; LTONEXT(keys))
	{
		inkey = LCONT(keys, t_sh_inkey*);	
		if (inkey == NULL ||
			(ft_strstr(" \t", (key = sh_inkey_get_meaning(inkey))) &&
			(ft_strchr("'\"\\`()", inkey->inside_of) == NULL)))
		{
			add_word(&words, &word_buf);
		}
		else
			ft_lstadd(&word_buf, ft_lstnew(cpy_inkey(inkey), sizeof(*inkey)));
	}
	add_word(&words, &word_buf);
	return words;
}
