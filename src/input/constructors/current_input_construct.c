#include "shinput.h"

t_current_input	current_input_construct(void)
{
	t_current_input	result;
	t_shinput_seq	seq;

	ft_bzero(&result, sizeof(result));
	seq = shinput_seq_construct();
	result.input = ft_memdup(&seq, sizeof(seq));
	return (result);
}
