#include "shinput.h"

void	input_seq_add_key(t_shinput_seq * const target, t_sh_inkey const key)
{
	t_list	*tmp;

	if (target)
	{
		tmp = ft_lstnew(&key, sizeof(key));
		if (tmp == NULL)
			ft_err_mem(1);
		ft_lstadd(&target->keys, tmp);
		target->count++;
	}
}
