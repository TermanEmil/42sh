#include "shlogic.h"

/*
** Extract the meaning of the given keys into a fresh string, with specific
** delimiters.
*/

static inline t_str	extract_str_from_keys(const t_lst_inkey *keys)
{
	const t_sh_inkey	*sh_inkey;
	const t_lst_inkey	*start;
	t_rostr				meaning;
	int					count;

	start = keys;	
	for (count = 0; keys; LTONEXT(keys), count++)
	{
		sh_inkey = LCONT(keys, t_sh_inkey*);
		if (sh_inkey == NULL)
			break;
		meaning = sh_inkey_get_meaning(sh_inkey);
		if (ft_strlen(meaning) != 1)
			break;
		if (!(meaning[0] == '_' || ft_isalnum(meaning[0])))
			break;
	}

	return ft_lst_njoin(
		start,
		(t_rostr (*)(const void*, size_t))&sh_inkey_get_meaning, NULL, count);
}

/*
** Extract the dollar key value starting from the given key. After that, look
** into local vars, then in env if there is suck a key. If not, add dollar
** symbol and finish, else add the the value.
*/

static inline void			add_processed_value(
								const t_lst_inkey *key,
								const t_shvars *shvars,
								t_lst_inkey **processed_word)
{
	t_sh_inkey			buf_key;
	t_str				dollar_key;
	t_rostr				htab_val;
	t_hashmem			hashmem_key;

	dollar_key = extract_str_from_keys(key->next);
	if (dollar_key == NULL)
		ft_err_mem(1);
	
	hashmem_key = new_hashmem_str(dollar_key);	
	htab_val = htab_get_strval(shvars->local, hashmem_key);
	if (htab_val == NULL)
		htab_val = htab_get_strval(shvars->env, hashmem_key);
	
	free(dollar_key);

	if (htab_val == NULL)
	{
		buf_key = sh_inkey_cpy_construct(LCONT(key, t_sh_inkey*));
		ft_lstadd(processed_word, ft_lstnew(&buf_key, sizeof(buf_key)));
		return;
	}

	ft_lstadd(processed_word, get_sh_inkeys_from_str(htab_val));
}

/*
** Make a processed copy of the given word.
*/

static inline t_lst_inkey	*process_dollar_in_word(
								const t_lst_inkey *word,
								const t_shvars *shvars)
{
	const t_lst_inkey	*key;
	const t_sh_inkey	*sh_inkey;
	t_lst_inkey			*processed_word;
	t_sh_inkey			buf_key;

	processed_word = NULL;
	for (key = word; key; LTONEXT(key))
		if ((sh_inkey = LCONT(key, t_sh_inkey*)) == NULL)
		{
			ft_lstadd(&processed_word, ft_lstnew(NULL, 0));
			continue;
		}
		else if (ft_strequ(sh_inkey_get_meaning(sh_inkey), "$") &&
			ft_strchr("'\\", sh_inkey->inside_of) == NULL)
		{
			add_processed_value(key, shvars, &processed_word);
		}
		else
		{
			buf_key = sh_inkey_cpy_construct(sh_inkey);
			ft_lstadd(&processed_word, ft_lstnew(&buf_key, sizeof(buf_key)));
		}
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
		processed_word = process_dollar_in_word(word, shvars);
		words->content = processed_word;
		ft_lstdel(&word, (t_ldel_func*)&sh_inkey_destruct);
	}
}
