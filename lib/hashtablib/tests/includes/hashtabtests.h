#ifndef HASHTABTESTS_H
# define HASHTABTESTS_H

# include "hashtablib.h"
# include "unittest.h"
# include "listlib.h"
# include "libft.h"

# define FREE_TESTS() ft_lstdel(&g_tests, &std_mem_del)

extern t_list	*g_tests;

void	basic_test(void);
void	new_hashmem_str_test(void);
void	new_hashmem_str_cp_test(void);
void	not_enough_space_test(void);
void	exceptional_test(void);
void	add_hashpair_with_nulls(void);
void	removal_test(void);
void	htab_get_next_pair_test(void);
void	test_htab_cmp_f(void);
void	index_of_test(void);

#endif