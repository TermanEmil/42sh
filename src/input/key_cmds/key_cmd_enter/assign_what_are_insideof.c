#include "shell42.h"

/*
** By parenthesis I mean: ()[]{}\`'"
*/

static void remove_last_bracket(t_list *brakets)
{
	ft_lstpop_back(&brakets, &std_mem_del);
}

static inline t_bool	process_last_br_as_bslash(
							char last_bracket,
							t_sh_inkey *inkey,
							t_list *brakets)
{
	if (last_bracket != '\\')
		return FALSE;

	if (inkey != NULL)
		inkey->inside_of = last_bracket;
	remove_last_bracket(brakets);
	return TRUE;
}

static inline t_bool	process_key_as_bslash(
							char last_bracket,
							t_sh_inkey *inkey,
							t_rostr key,
							t_list *brakets)
{
	if (ft_strequ(key, "\\") && last_bracket != '\'')
	{
		ft_lstadd(&brakets, ft_lstnew_str(key));
		inkey->inside_of = CHAR_PARENTHESIS_LIM;
		return TRUE;
	}
	return FALSE;
}

static inline t_bool	process_single_quote(
							char last_bracket,
							t_sh_inkey *inkey,
							t_rostr key,
							t_list *brakets)
{
	if (ft_strequ(key, "'"))
	{
		inkey->inside_of = CHAR_PARENTHESIS_LIM;
		if (last_bracket == '\'')
			remove_last_bracket(brakets);
		else
			ft_lstadd(&brakets, ft_lstnew_str(key));
		return TRUE;
	}
	return FALSE;
}

static inline int	process_real_brackets(
						t_rostr key,
						const char last_bracket,
						t_list *brakets)
{
	if (ft_strstr("()[]{}", key))
	{
		if (ft_strstr(")]}", key))
		{
			if (key[0] == ft_get_matching_parenthesis(last_bracket))
				remove_last_bracket(brakets);
			else
			{
				term_putnewl();
				ft_error(FALSE, "%s: Syntax error, unexpected `%c'.",
					g_proj_name, key[0]);
				return -1;
			}
		}
		else
			ft_lstadd(&brakets, ft_lstnew_str(key));
		return TRUE;
	}
	return FALSE;
}

/*
** Assign each key what they're inside of:
** in:  a"b'c"d'e"f\ab
** out: .&"&'''&"&.&\.
** Where the symbold & means it's a 'bracket'. The dot means it's not inside of
** anything.
**
** Return -1 if an unexpected bracked has been found.
** Return the bracket that hasn't been closed, or 0 if there isn't one.
*/

char					assign_what_are_insideof(t_lst_inkey *keys)
{
	t_list		*brakets;
	char		last_bracket;
	t_rostr		key;
	t_sh_inkey	*inkey;
	int			ret;

	brakets = ft_lstnew_str(".");
	for (int i = 0; keys; LTONEXT(keys), i++)
	{
		last_bracket = *LSTR(ft_lst_get_last(brakets));
		inkey = LCONT(keys, t_sh_inkey*);
		key = sh_inkey_get_meaning(inkey);

		if (process_last_br_as_bslash(last_bracket, inkey, brakets))
			continue;

		if (keys->content == NULL)
			continue;
		inkey->inside_of = last_bracket;

		if (process_key_as_bslash(last_bracket, inkey, key, brakets))
			continue;

		if (ft_strstr("()[]{}`'\"", key) == NULL)
			continue;

		if (process_single_quote(last_bracket, inkey, key, brakets))
			continue;

		if (ft_strchr("'\\", last_bracket))
			continue;

		inkey->inside_of = CHAR_PARENTHESIS_LIM;

		if ((ret = process_real_brackets(key, last_bracket, brakets)) == -1)
		{
			ft_lstdel(&brakets, &std_mem_del);
			return ret;
		}
		else if (ret == TRUE)
			continue;

		if (key[0] == last_bracket)
			remove_last_bracket(brakets);
		else
			ft_lstadd(&brakets, ft_lstnew_str(key));
	}

	last_bracket = (char)*LSTR(ft_lst_get_last(brakets));
	ft_lstdel(&brakets, &std_mem_del);
	return (last_bracket == '.') ? 0 : last_bracket;
}