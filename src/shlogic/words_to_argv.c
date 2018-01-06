#include "shlogic.h"

static inline t_rostr	get_ptrkey_meaning(const void *key_mem, size_t size)
{
	const t_sh_inkey	*key;

	(void)size;
	key = ((t_sh_inkey*)key_mem);
	if (key->inside_of == CHAR_PARENTHESIS_LIM && 
		ft_strstr("'\"\\`", sh_inkey_get_meaning(key)) != NULL)
		return "";
	else
		return sh_inkey_get_meaning(key);
}

t_str					word_to_argv(const t_lst_inkey *keys)
{
	return ft_lst_join((void*)keys, &get_ptrkey_meaning, NULL);
}

/*
** Make an array of strings from the given 'words'. The quotes are not excluded.
*/

t_str					*words_to_argv(t_lst_words *words)
{
	t_str	*argv;
	t_str	str_word;
	int		i;

	if (words == NULL)
		return NULL;

	argv = (t_str*)malloc(sizeof(t_str) * (ft_lstlen(words) + 1));
	if (argv == NULL)
		ft_err_mem(1);
	for (i = 0; words; LTONEXT(words), i++)
	{
		str_word = word_to_argv(LCONT(words, const t_lst_inkey*));
		if (str_word == NULL)
			ft_err_mem(1);

		argv[i] = str_word;
	}
	argv[i] = NULL;
	return argv;
}