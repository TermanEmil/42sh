#include "shell42.h"

static inline void		set_parenthesis_prompt(
							t_str const buf, char const parenthesis)
{
	buf[0] = 0;
	if (parenthesis != '\\')
		ft_strcat(buf, ft_char_to_str(parenthesis));

	ft_strcat(buf, ">");
}

/*
** The line_index is reset in the key_cmd_enter()
*/

static inline void		process_complete_parenthesis(void)
{
	ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);

	if (g_shinput->history.tmp_current_in)
	{
		shinput_seq_destruct(g_shinput->history.tmp_current_in);
		g_shinput->history.tmp_current_in = NULL;
	}
	g_shinput->history.current_in_index = -1;
}

static inline void		process_unexpected_parenthesis(char const parenthesis)
{
	ft_strcpy(g_shdata.prompt, DEFAULT_PROMPT);

	g_current_in->line_index = 0;

	term_putnewl();
	ft_error(FALSE, "%s: Syntax error, unexpected `%c'.",
		g_proj_name, -parenthesis);

	g_shinput->history.current_in_index = -1;
}

static inline void		process_incomplete_parenthesis(char const parenthesis)
{
	set_parenthesis_prompt(g_shdata.prompt, parenthesis);

	g_current_in->line_index++;
	g_shinput->history.current_in_index = -1;
}

/*
** Returns 0 if the input is ready for further processing.
*/

int						key_cmd_enter_process_parenthesis(void)
{
	char const	parenthesis = current_input_is_complete(g_current_in);
	int			ret;

	ret = 0;
	if (parenthesis == 0)
	{
		process_complete_parenthesis();
		ret = 0;
	}
	else if (parenthesis < 0)
	{
		process_unexpected_parenthesis(parenthesis);
		ret = -1;
	}
	else
	{
		process_incomplete_parenthesis(parenthesis);
		ret = 1;
	}
	return (ret);
}
