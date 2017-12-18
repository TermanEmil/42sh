#include "shinput.h"

/*
** Makes a full copy of the given seq.
*/

t_shinput_seq	*input_seq_cpy(t_shinput_seq const * const seq)
{
	t_shinput_seq	*result;

	result = malloc(sizeof(t_shinput_seq));
	if (result == NULL)
		ft_err_mem(1);
	*result = shinput_seq_construct();
	result->keys = ft_lst_full_cpy(seq->keys, (t_lcpy_cont*)&sh_inkey_cpy,
		(t_ldel_func*)&sh_inkey_destruct);

	if (result->keys == NULL && seq->keys != NULL)
		ft_err_mem(1);

	result->count = seq->count;
	return (result);
}
