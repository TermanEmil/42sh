#include "shlogic.h"

static int		add_tilde_val_to_word(
					t_lst_inkey **word,
					const t_lst_inkey *tilde_key,
					const t_shvars *shvars)
{
	t_str		tilde_prefix;
	int			tilde_prefix_len;
	t_str		tilde_val;

	tilde_prefix = get_tilde_prefix(tilde_key->next, &tilde_prefix_len);
	if (tilde_prefix == NULL)
		ft_err_mem(1);

	tilde_val = get_tilde_value(tilde_prefix, shvars);
	free(tilde_prefix);

	if (tilde_val == NULL)
		add_cpykey_to_list(word, LCONT(tilde_key, t_sh_inkey*));
	else
		ft_lstadd(word, get_sh_inkeys_from_str(tilde_val));
	free(tilde_val);
	return (tilde_val == NULL) ? 0 : tilde_prefix_len;
}

/*
** First part of the logic.
** Return TRUE, if the current_key was processed.
*/

static t_bool		handle_basic_case(
						t_lst_inkey **processed_word,
						const t_lst_inkey **current_key,
						const t_shvars *shvars)
{
	const t_sh_inkey	*sh_inkey;

	sh_inkey = LCONT(*current_key, t_sh_inkey*);
	if (sh_inkey == NULL ||
		!ft_strequ(sh_inkey_get_meaning(sh_inkey), "~") ||
		ft_strchr("\'\"\\", sh_inkey->inside_of) != NULL)
	{
		add_cpykey_to_list(processed_word, sh_inkey);
		return TRUE;
	}

	if (LPREV(*current_key) == NULL || LPREV(*current_key)->content == NULL)
	{
		*current_key = ft_lstget(*current_key,
			add_tilde_val_to_word(processed_word, *current_key, shvars));
		return TRUE;
	}
	return FALSE;
}

static t_bool		sh_inkey_is_valid_key_for_tilde_name(
						const t_sh_inkey *sh_inkey)
{
	return !ft_strchr("\"\'\\", sh_inkey->inside_of) &&
			sh_inkey->inside_of != CHAR_PARENTHESIS_LIM &&
			is_valid_var_name_inkey(sh_inkey);
}

static t_bool		handle_second_case(
						t_lst_inkey **processed_word,
						const t_lst_inkey **current_key,
						const t_shvars *shvars)
{
	const t_sh_inkey	*sh_inkey;

	sh_inkey = LCONT(LPREV(*current_key), t_sh_inkey*);
	if (ft_strchr("\'\"\\" , sh_inkey->inside_of) == NULL &&
		sh_inkey->inside_of != CHAR_PARENTHESIS_LIM)
	{
		if (ft_strstr(" \t;|><:", sh_inkey_get_meaning(sh_inkey)))
		{
			*current_key = ft_lstget(*current_key,
				add_tilde_val_to_word(processed_word, *current_key, shvars));
			return TRUE;
		}
		else if (ft_strstr("=", sh_inkey_get_meaning(sh_inkey)) &&
			LPREV(*current_key)->prev && LPREV(*current_key)->prev->content)
		{
			sh_inkey = LCONT(LPREV(*current_key)->prev, t_sh_inkey*);
			if (sh_inkey_is_valid_key_for_tilde_name(sh_inkey))
			{
				*current_key = ft_lstget(*current_key, add_tilde_val_to_word(
					processed_word, *current_key, shvars));
				return TRUE;
			}
		}
	}
	return FALSE;
}

/*
** Process the tilde value in the given word, returning a fresh processd copy
** of the word.
*/

t_lst_inkey			*process_tilde_in_word(
						const t_lst_inkey *word,
						const t_shvars *shvars)
{
	const t_lst_inkey	*key;
	t_lst_inkey			*processed_word;

	processed_word = NULL;
	for (key = word; key; LTONEXT(key))
	{
		if (handle_basic_case(&processed_word, &key, shvars))
			continue;
		if (handle_second_case(&processed_word, &key, shvars))
			continue;
		add_cpykey_to_list(&processed_word, LCONT(key, t_sh_inkey*));
	}
	return processed_word;
}