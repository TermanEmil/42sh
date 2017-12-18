#include "shinput.h"

void	input_seq_insert_seq(t_shinput_seq * const seq, size_t const index,
			t_shinput_seq * const to_insert)
{
	if (ft_lst_insert_range(&seq->keys, index, to_insert->keys) == 0)
		seq->count += to_insert->count;
}
