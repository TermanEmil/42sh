#include "shlogic.h"

void	debug_print_groups_of_words(const t_grps_wrds *groups_of_words)
{
	t_str		*argv;
	int			i;

	for (i = 0; groups_of_words; LTONEXT(groups_of_words), i += 3)
	{
		argv = words_to_argv(LCONT(groups_of_words, t_lst_words*));
		debug_print_strings(argv, i);
		ft_free_bidimens(argv);
	}
}
