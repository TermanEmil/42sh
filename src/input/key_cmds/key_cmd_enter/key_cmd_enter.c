#include "shell42.h"
#include "shlogic.h"

/*
** Print the current input and each key's 'inside_of' value at the top of the
** screen.
*/

static inline void	print_debug_information(t_list *keys)
{
	t_str	insideof_map;
	t_str	input_txt;

	input_txt = current_input_all_lines_to_str(g_current_in, "");
	insideof_map = get_keys_insideof_map(keys);

	term_printf(0, 0, "input:       %s", input_txt);
	term_printf(0, 1, "isideof_map: %s", insideof_map);

	free(input_txt);
	free(insideof_map);
}

static inline void	set_parenthesis_prompt(t_str buf, char parenthesis)
{
	buf[0] = 0;
	if (parenthesis != '\\')
		ft_strcat(buf, ft_char_to_str(parenthesis));

	ft_strcat(buf, ">");
}

static inline int	process_bracket_completion(int assign_what_are_insideof_ret)
{
	int		ret;

	ret = assign_what_are_insideof_ret;

	g_shinput->history.current_in_index = -1;
	if (ret > 0)
	{
		set_parenthesis_prompt(g_shdata.prompt, ret);
		g_current_in->line_index++;
	}
	else if (ret == -1)
	{
		ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);
		g_current_in->line_index = 0;
	}
	else
	{
		ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);	
		if (g_shinput->history.tmp_current_in)
		{
			shinput_seq_destruct(g_shinput->history.tmp_current_in);
			g_shinput->history.tmp_current_in = NULL;
		}
		g_current_in->line_index = 0;
		return 0;
	}
	return 1;
}

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
	static const char	*delims = " \t";
	t_bool				is_new_word;

	words = NULL;
	word_buf = NULL;
	for (; keys; LTONEXT(keys))
	{
		inkey = LCONT(keys, t_sh_inkey*);
	

		if (inkey == NULL ||
			(ft_strstr(delims, (key = sh_inkey_get_meaning(inkey))) &&
			(ft_strchr("`'\"", inkey->inside_of) == NULL)))
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

t_rostr	get_ptrkey_meaning(const void *key, size_t size)
{
	(void)size;
	return sh_inkey_get_meaning(*((t_sh_inkey**)key));
}

t_str	*words_to_argv(t_lst_words *words)
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
		str_word = ft_lst_join(
			*LCONT(words, t_lst_inkey**),
			&get_ptrkey_meaning, NULL);

		if (str_word == NULL)
			ft_err_mem(1);

		argv[i] = str_word;
	}
	argv[i] = NULL;
	return argv;
}

void	ft_print_strings(t_str *strings)
{
	int		i;

	if (strings == NULL)
		return;
	for (i = 0; strings[i]; i++)
		term_printf(0, 2 + i, "%d) %s", i, strings[i]);
}

int		key_cmd_enter(void)
{
	int				ret;
	t_lst_inkey		*keys;

	input_reprint(g_current_in);

	keys = current_in_all_lines_to_lst(g_current_in, &g_shinput->history);
	ret = assign_what_are_insideof(keys);
	// print_debug_information(keys);
	if (process_bracket_completion(ret) == 0)
	{
		t_lst_words	*words;
		t_str		*argv;

		words = extract_words_from_keys(keys);
		argv = words_to_argv(words);
		ft_print_strings(argv);

	}

	input_mv_current_in_to_history(g_shinput);
	term_putnewl();
	input_reprint_here(g_current_in);

	ft_lstdel(&keys, NULL);
	return (0);
}