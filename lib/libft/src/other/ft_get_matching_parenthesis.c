#include "libft.h"

char		ft_get_matching_parenthesis(char const parenthesis)
{
	switch (parenthesis)
	{
		case '(':
			return (')');
		case '[':
			return (']');
		case '{':
			return ('}');
		case ')':
			return ('(');
		case ']':
			return ('[');
		case '}':
			return ('{');
	}
	if (ft_strchr("\"`'", parenthesis))
		return (parenthesis);
	return (0);
}
