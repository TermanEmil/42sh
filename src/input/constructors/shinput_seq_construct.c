#include "shinput.h"

t_shinput_seq	shinput_seq_construct(void)
{
	t_shinput_seq	result;

	ft_bzero(&result, sizeof(result));
	return (result);
}

t_shinput_seq	*shinput_seq_new(void)
{
	t_shinput_seq	*result;
	t_shinput_seq	buf;

	buf = shinput_seq_construct();
	result = ft_memdup(&buf, sizeof(buf));
	
	if (result == NULL)
		ft_err_mem(1);

	return (result);
}