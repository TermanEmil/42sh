#include "shinput.h"

/*
** Checks if the given `current_in' is complete: all parenthesis (including
** quote) are closed. Also handles the backslash.
** If the it's incomplete, the unmatching parenthesis is returned.
*/

char	current_input_is_complete(t_current_input const * const input)
{
	t_str	str;
	char	result;

	str = current_input_all_lines_to_str(input, " ");
	result = ft_str_shell_parenthesis_are_complete(str);
	free(str);
	return (result);
}
