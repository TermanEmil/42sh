#include "unittest.h"

void	add_test(t_list ** head, t_unittest * new_test)
{
	ft_lstadd(head, ft_lstnew(new_test, sizeof(t_unittest)));
}