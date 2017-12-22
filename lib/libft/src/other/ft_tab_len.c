#include <unistd.h>

/*
** Count how many non null elements the given tab has.
*/

int		ft_tab_len(const void **tab)
{
	const void	**start;

	start = tab;
	while (*tab != NULL)
		tab++;
	return tab - start;
}
