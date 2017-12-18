#include "listlib.h"

/*
** parenthesis, in this case means: "'`()[]{}
*/

/*
** Does multiple things:
**   1) Checks if the current character is matching the last one, if so, remove
**   the last parenthesis from the stack.
**   2) Checks if it's an unexpected parenthesis
**   3) Adds the current character to the stack. (It's considered to be a
**   parenthesis).
*/

static inline char		main_parenthesis_processing(
							char const last_c,
							char const current_c,
							t_list ** const stack_head)
{
	if (last_c != 0 && current_c == ft_get_matching_parenthesis(last_c))
		ft_lstpop_back(stack_head, &std_mem_del);
	else if (ft_strchr(")]}", current_c))
		return (-current_c);
	else
		ft_lstadd(stack_head, ft_lstnew(&current_c, sizeof(char)));
	return (0);
}

/*
** The quotes need a bit of special treatment. Returns TRUE in case if the
** current character is such a quote
*/

static inline t_bool	process_quotes(
							char const last_c,
							char const current_c,
							t_list ** const stack_head)
{
	if (last_c == '\'' || last_c == '\"' || last_c == '`')
	{
		if (current_c == last_c)
			ft_lstpop_back(stack_head, &std_mem_del);
		return (TRUE);
	}
	else
		return (FALSE);
}

/*
** The preprocessing part from the `for' loop, from the core part.
** return True if the given current character should be skipped.
*/

static inline t_bool	pre_process(
							char const current_c,
							t_bool * const is_back_slash)
{
	if (current_c == '\\')
	{
		*is_back_slash = !*is_back_slash;
		return (TRUE);
	}

	if (ft_strchr("()[]{}`'\"", current_c) == NULL)
	{
		*is_back_slash = FALSE;
		return (TRUE);
	}

	return (FALSE);
}

/*
** This is the core part of the function
** Returns something in case of unexpected parenthesis, e.g.: "abc)". In this
** case -')' will be returned (negative value).
*/

static inline char		core_check_balanced(
							t_rostr const str,
							t_list ** const stack_head,
							t_bool * const is_back_slash)
{
	int		i;
	char	last_c;
	char	ret;

	for (i = 0; str[i]; i++)
	{
		if (pre_process(str[i], is_back_slash))
			continue;

		last_c = LCONT(ft_lst_get_last(*stack_head), char*)[0];
		
		if (last_c != '\'' && *is_back_slash)
			*is_back_slash = FALSE;
		else if (process_quotes(last_c, str[i], stack_head))
			ft_pass();
		else if ((ret = main_parenthesis_processing(last_c, str[i], stack_head)))
			return (ret);
		*is_back_slash = FALSE;
	}
	return (0);
}

/*
** Check if the given string is complete:
** 		all braces are closed and all quotes are closed by shell standarts
**
** Return a positive value in case the string is incomplete
** -<parenthesis> (negative value) is returned in case of unxepected parenthesis
** 0 if it's complete
*/

char					ft_str_shell_parenthesis_are_complete(t_rostr const str)
{
	t_list	*stack_head;
	char	last_c;
	t_bool	is_back_slash;
	int		ret;

	stack_head = ft_lstnew("", sizeof(char));
	is_back_slash = FALSE;

	ret = core_check_balanced(str, &stack_head, &is_back_slash);
	
	last_c = LCONT(ft_lst_get_last(stack_head), char*)[0];
	ft_lstdel(&stack_head, &std_mem_del);

	if (ret)
		return (ret);
	return ((is_back_slash) ? '\\' : last_c);
}
