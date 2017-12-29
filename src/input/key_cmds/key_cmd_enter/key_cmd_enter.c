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

void	shlogic_exec(t_lst_words *words)
{
	//- Divide in subcommands: ; | > >> < <<

	//-	Process dollar values
	//-	Process tilda value ~

	//-	Find what command it is:
	//		is it referring to a specific pointed program?
	//		is it a built in cmd?
	//		is it a program from PATH?
}

int		key_cmd_enter(void)
{
	int				ret;
	t_lst_inkey		*keys;

	input_reprint(g_current_in);

	keys = current_in_all_lines_to_lst(g_current_in, &g_shinput->history);
	ret = assign_what_are_insideof(keys);
	if (process_bracket_completion(ret) == 0)
	{
		t_lst_words	*words;
		t_lst_words	*tmp_words;
		t_str		*argv;

		words = extract_words_from_keys(keys);
		
		tmp_words = divide_by_redirections(words);
		del_lst_of_words_not_content(words);
		words = tmp_words;
		
		process_dollar_values(words, &g_shdata.shvars);
		proceess_tilde(words, &g_shdata.shvars);

		argv = words_to_argv(words);
		debug_print_strings(argv);
		ft_free_bidimens(argv);
		del_lst_of_words(words);
	}

	input_mv_current_in_to_history(g_shinput);
	term_putnewl();
	input_reprint_here(g_current_in);

	ft_lstdel(&keys, NULL);
	return (0);
}