#include "shlogic.h"

/*
** Extract the dollar key value starting from the given key. After that, look
** into local vars, then in env if there is suck a key. If not, add dollar
** symbol and finish, else add the the value.
*/

static inline int			add_processed_value_(
								const t_lst_inkey *key,
								const t_shvars *shvars,
								t_lst_inkey **processed_word)
{
	t_str				dollar_key;
	int					dollar_key_len;
	t_rostr				htab_val;
	t_hashmem			hashmem_key;

	dollar_key = extract_var_name_from_keys(key->next);
	if (dollar_key == NULL)
		ft_err_mem(1);

	hashmem_key = new_hashmem_str(dollar_key);	
	htab_val = htab_get_strval(shvars->local, hashmem_key);
	if (htab_val == NULL)
		htab_val = htab_get_strval(shvars->env, hashmem_key);

	dollar_key_len = ft_strlen(dollar_key);
	free(dollar_key);

	if (htab_val == NULL)
		return dollar_key_len;

	ft_lstadd(processed_word, get_sh_inkeys_from_str(htab_val));
	return dollar_key_len;
}

/*
** Make a processed copy of the given word.
*/

static inline t_lst_inkey	*process_dollar_in_word_(
								const t_lst_inkey *word,
								const t_shvars *shvars)
{
	const t_lst_inkey	*key;
	const t_sh_inkey	*sh_inkey;
	t_lst_inkey			*processed_word;
	int					keys_count;

	processed_word = NULL;
	for (key = word; key; LTONEXT(key))
		if ((sh_inkey = LCONT(key, t_sh_inkey*)) == NULL)
		{
			ft_lstadd(&processed_word, ft_lstnew(NULL, 0));
			continue;
		}
		else if (ft_strequ(sh_inkey_get_meaning(sh_inkey), "$") &&
			ft_strchr("'\\()`", sh_inkey->inside_of) == NULL)
		{
			keys_count = add_processed_value_(key, shvars, &processed_word);
			key = ft_lstget(key, keys_count);
		}
		else
			add_cpykey_to_list(&processed_word, sh_inkey);
	return processed_word;
}

/*
** Substitute dollar stuff with variables where it's possible.
*/

void						process_dollar_values(
								t_lst_words *words,
								const t_shvars *shvars)
{
	t_lst_inkey	*processed_word;
	t_lst_inkey	*word;

	for (; words; LTONEXT(words))
	{
		if (words->content == NULL)
			continue;

		word = LCONT(words, t_lst_inkey*);
		processed_word = process_dollar_in_word_(word, shvars);
		words->content = processed_word;
		ft_lstdel(&word, (t_ldel_func*)&sh_inkey_destruct);
	}
}
