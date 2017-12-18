#include "shell42.h"

void	print_lst_of_words(t_list *words)
{
	int		i;

	term_save_cursor_pos();
	term_cursor_goto(0, 2);
	i = 0;
	while (words)
	{
		term_clear_from_cursor_to_end_line();
		t_str word = lst_in_key_get_pure_str(*LCONT(words, t_lst_inkey**), "; ");
		ft_printf("%d) %s", i, word);
		term_putnewl();
		free(word);
		i++;
		LTONEXT(words);
	}
	term_restore_cursor_pos();
}

t_lst_words	*sh_inkeys_process_shinkeys(t_lst_inkey *keys)
{
	t_list		*lst_brakets;
	t_bool		is_bslash;
	t_rostr		last_bracket;
	t_rostr		this_key;
	t_sh_inkey	*shinkey;
	int			word_index;

	t_list		*lst_of_words;
	t_lst_inkey	*current_word;

	lst_of_words = NULL;
	current_word = NULL;

	is_bslash = FALSE;
	lst_brakets = ft_lstnew_str("");
	word_index = 0;
	for (; keys; LTONEXT(keys))
	{
		if (keys->content == NULL)
		{
			is_bslash = FALSE;
			// word_index++;
			ft_lstadd(&lst_of_words, ft_lstnew(&current_word, sizeof(void*)));
			current_word = NULL;
			continue;
		}

		last_bracket = LSTR(ft_lst_get_last(lst_brakets));
		shinkey = LCONT(keys, t_sh_inkey*);
		this_key = sh_inkey_get_meaning(shinkey);

		// shinkey->word_id = word_index;

		if (ft_strequ(this_key, "\\") && !ft_strequ(last_bracket, "'"))
		{
			if (is_bslash)
			{
				ft_lstadd(&current_word, ft_lstcpy_one(keys));
				shinkey->is_true_char = TRUE;
			}

			is_bslash = !is_bslash;
			continue;
		}

		if (ft_strstr(" \t\n", this_key) != NULL)
		{
			if (last_bracket[0] == 0 || ft_strstr("\"'`", last_bracket) == NULL)
			{
				// word_index++;
				ft_lstadd(&lst_of_words, ft_lstnew(&current_word, sizeof(void*)));
				current_word = NULL;
				// shinkey->word_id = -1;
				continue;
			}
		}

		if (ft_strstr("()[]{}`'\"", this_key) == NULL)
		{
			is_bslash = FALSE;
			ft_lstadd(&current_word, ft_lstcpy_one(keys));
			shinkey->is_true_char = TRUE;
			continue;
		}

		if (!ft_strequ(last_bracket, "\'") && is_bslash)
		{
			ft_lstadd(&current_word, ft_lstcpy_one(keys));
			shinkey->is_true_char = TRUE;
			// LCONT(keys, t_sh_inkey*)->is_true_char = TRUE;
		}
		else if (last_bracket[0] != 0 && ft_strstr("\'\"`", last_bracket))
		{
			if (ft_strequ(last_bracket, this_key))
			{
				ft_lstpop_back(&lst_brakets, &std_mem_del);
				// shinkey->word_id = -1;

				// ft_lstadd(&lst_of_words, ft_lstnew(&current_word, sizeof(void*)));
				// current_word = NULL;
			}
			else
			{
				ft_lstadd(&current_word, ft_lstcpy_one(keys));
				shinkey->is_true_char = TRUE;
			}
		}
		else
		{
			if (last_bracket[0] != 0 &&
				ft_strequ(this_key, ft_char_to_str(
					ft_get_matching_parenthesis(last_bracket[0]))))
			{
				ft_lstpop_back(&lst_brakets, &std_mem_del);
				// shinkey->word_id = -1;
			}
			else if (ft_strstr(")]}", this_key))
				ft_fatal("Internal error current_in_process_key_meaning() [2]");
			else
			{
				ft_lstadd(&lst_brakets, ft_lstnew_str(this_key));
				// shinkey->word_id = -1;
			}
		}
		is_bslash = FALSE;
	}
	ft_lstadd(&lst_of_words, ft_lstnew(&current_word, sizeof(void*)));
	ft_lstdel(&lst_brakets, &std_mem_del);
	return (lst_of_words);
}

void	ft_bidimens_print(t_str const *tab)
{
	int		i;

	term_save_cursor_pos();
	term_cursor_goto(0, 3);

	for (i = 0; tab[i]; i++)
	{
		ft_printf("%d) %s", i, tab[i]);
		term_putnewl();
	}
	term_restore_cursor_pos();
}

int		key_cmd_enter(void)
{
	int				ret;
	t_lst_inkey		*keys;
	t_lst_words		*lst_of_words;
	t_str			*argv;

	input_reprint(g_current_in);

	do
	{	
		ret = key_cmd_enter_process_parenthesis();
		if (ret != 0)
			break;

		keys = current_in_all_lines_to_lst(g_current_in, &g_shinput->history);
		lst_of_words = sh_inkeys_process_shinkeys(keys);
		
		// print_lst_of_words(lst_of_words);
		argv = lst_of_words_to_argv(lst_of_words);
		ft_bidimens_print(argv);

		ft_free_bidimens(argv);
		
		lst_of_words_del(lst_of_words);
		ft_lstdel(&keys, NULL);

		g_current_in->line_index = 0;
	} while (FALSE);

	input_mv_current_in_to_history(g_shinput);

	term_putnewl();
	input_reprint_here(g_current_in);

	return (0);
}