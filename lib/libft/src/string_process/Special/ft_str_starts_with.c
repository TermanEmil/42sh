#include "libft.h"

t_bool	ft_str_starts_with(t_rostr haystack, t_rostr needle)
{
	return ft_strnequ(haystack, needle, ft_strlen(needle));
}
