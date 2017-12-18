#include "shinput.h"

void	input_seq_insert_key(t_shinput_seq * const seq,
			t_sh_inkey const key, size_t const index)
{
	t_list	*lst_key;

	if (seq == NULL)
		return;
	lst_key = ft_lstnew(&key, sizeof(key));
	if (lst_key == NULL)
		ft_err_mem(1);
	if (ft_lstinsert(&seq->keys, index, lst_key, NULL) == 0)
		seq->count++;
}
