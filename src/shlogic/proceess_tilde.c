#include "shlogic.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static inline t_str			get_tilde_prefix(const t_lst_inkey *keys, int *len)
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
		if (sh_inkey->inside_of == CHAR_PARENTHESIS_LIM ||
			ft_strstr(" \t/", meaning))
		{
			break;
		}
	}

	*len = count;
	return ft_lst_njoin(
		start,
		(t_rostr (*)(const void*, size_t))&sh_inkey_get_meaning, NULL, count);
}

static inline t_str			get_tilde_value(
								t_rostr tilde_prefix,
								const t_shvars *shvars)
{
	t_str			result;
	struct passwd 	*buf_passwd;

	if (ft_strequ(tilde_prefix, ""))
	{
		result = ft_strdup(
			htab_get_strval(shvars->env, new_hashmem_str("HOME")));
		if (result == NULL)
			result = ft_strdup(getpwuid(getuid())->pw_dir);
	}
	else
	{
		buf_passwd = getpwnam(tilde_prefix);
		if (buf_passwd == NULL)
			result = NULL;
		else
			result = ft_strdup(buf_passwd->pw_dir);
	}

	return result;
}

void	add_key_to_word(
			t_lst_inkey **word,
			const t_sh_inkey *sh_inkey)
{
	t_sh_inkey buf_key;

	buf_key = sh_inkey_cpy_construct(sh_inkey);
	ft_lstadd(word, ft_lstnew(&buf_key, sizeof(buf_key)));
}

int		add_tilde_val_to_word(
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
		add_key_to_word(word, LCONT(tilde_key, t_sh_inkey*));
	else
		ft_lstadd(word, get_sh_inkeys_from_str(tilde_val));
	free(tilde_val);
	return (tilde_val == NULL) ? 0 : tilde_prefix_len;
}

static inline t_lst_inkey	*process_tilde_in_word(
								const t_lst_inkey *word,
								const t_shvars *shvars)
{
	const t_lst_inkey	*key;
	const t_sh_inkey	*sh_inkey;
	t_lst_inkey			*processed_word;
	t_rostr				meaning;

	processed_word = NULL;
	for (key = word; key; LTONEXT(key))
	{
		sh_inkey = LCONT(key, t_sh_inkey*);
		if (sh_inkey == NULL ||
			!ft_strequ(sh_inkey_get_meaning(sh_inkey), "~") ||
			ft_strchr("\'\"\\", sh_inkey->inside_of) != NULL)
		{
			add_key_to_word(&processed_word, sh_inkey);
			continue;
		}

		if (key->prev == NULL || key->prev->content == NULL)
		{
			key = ft_lst_roget(key, add_tilde_val_to_word(&processed_word, key, shvars));
			continue;
		}

		sh_inkey = LCONT(key->prev, t_sh_inkey*);
		meaning = sh_inkey_get_meaning(sh_inkey);

		if (ft_strchr("\'\"\\" , sh_inkey->inside_of) == NULL &&
			sh_inkey->inside_of != CHAR_PARENTHESIS_LIM)
		{
			if (ft_strstr(" \t;|><:", meaning))
			{
				key = ft_lst_roget(key, add_tilde_val_to_word(&processed_word, key, shvars));
				continue;
			}

			if (ft_strstr(" \t;|><:", meaning) ||
				(ft_strstr("=", meaning) &&
				key->prev->prev && key->prev->prev->content))
			{
				sh_inkey = LCONT(key->prev->prev, t_sh_inkey*);
				meaning = sh_inkey_get_meaning(sh_inkey);
				if (!ft_strchr("\"\'\\", sh_inkey->inside_of) &&
					sh_inkey->inside_of != CHAR_PARENTHESIS_LIM &&
					is_valid_var_name_inkey(sh_inkey))
				{
					key = ft_lst_roget(key, add_tilde_val_to_word(&processed_word, key, shvars));
					continue;
				}
			}
		}
		add_key_to_word(&processed_word, LCONT(key, t_sh_inkey*));
	}
	return processed_word;
}

/*
** Substitute tilda.
*/

void	proceess_tilde(t_lst_words	*words, const t_shvars *shvars)
{
	t_lst_inkey	*processed_word;
	t_lst_inkey	*word;

	for (; words; LTONEXT(words))
	{
		if (words->content == NULL)
			continue;

		word = LCONT(words, t_lst_inkey*);
		processed_word = process_tilde_in_word(word, shvars);
		words->content = processed_word;
		ft_lstdel(&word, (t_ldel_func*)&sh_inkey_destruct);
	}
}
