#include "shlogic.h"

/*
** Delete the given groups of words (only the group and [word structure]~).
*/

void	del_groups_of_words(t_grps_wrds *groups_of_words)
{
	t_grps_wrds	*group;
	t_lst_words	*words;

	for (group = groups_of_words; group; LTONEXT(group))
	{
		words = LCONT(group, t_lst_words*);
		ft_lstdel(&words, NULL);
	}
	ft_lstdel(&groups_of_words, NULL);
}
