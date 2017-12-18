#ifndef EVENTLIBTESTS_H
# define EVENTLIBTESTS_H

# include "eventlib.h"

# define FREE_TESTS() ft_lstdel(&g_tests, &std_mem_del)

extern t_list	*g_tests;

void	general_test(void);
void	remove_add_test(void);

#endif