#ifndef SHTESTS_H
# define SHTESTS_H

# include "unittest.h"
# include "shell42.h"
# include "shdisplay.h"
# include "shinput.h"
# include "ft_errors.h"

# define FREE_TESTS() ft_lstdel(&g_tests, &std_mem_del)

extern t_list	*g_tests;

void			memleak_1_shdisplay(void);
void			memleak_1_shinput(void);
void			shinput_seq_test_1(void);
void			input_history_test_add_pop(void);

#endif