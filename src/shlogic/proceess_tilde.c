#include "shlogic.h"

static inline t_bool		word_contains_valid_tilde(const t_lst_inkey *word)
{
	t_sh_inkey			*sh_inkey;
	t_rostr				*key_meaning;
	const t_lst_inkey	*key;

	for (key = word; key; LTONEXT(key))
	{
		sh_inkey = LCONT(key, t_sh_inkey*);
		if (sh_inkey == NULL)
			continue;

		if (!ft_strequ(sh_inkey_get_meaning(sh_inkey), "~"))
			continue;
		if (ft_strchr("\'\"\\", sh_inkey->inside_of) != NULL)
			continue;

		if (key->prev == NULL)
		{}
		// if (ft_strstr(" \t", const char *needle) sh_inkey_get_meaning(LCONT(key->prv, t_sh_inkey*)))
	}
	return TRUE;
}

static inline t_lst_inkey	*process_tilde(
								const t_lst_inkey *word,
								const t_shvars *shvars)
{
	return NULL;
}

/*
** Substitute tilda.
*/

void	proceess_tilde(t_lst_words	*words, const t_shvars *shvars)
{
	
}
