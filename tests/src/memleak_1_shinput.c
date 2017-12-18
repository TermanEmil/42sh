#include "shtests.h"

void	memleak_1_shinput(void)
{
	t_shinput		input;
	t_shinput_seq	seq;

	input = shinput_construct();
	seq = shinput_seq_construct();
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("^["),
		ft_strdup("\033")));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("a"),
		NULL));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("B"),
		NULL));
	input_history_add_seq(&input.history, seq);
	seq = shinput_seq_construct();
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("^["),
		ft_strdup("\033")));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("a"),
		NULL));
	input_history_add_seq(&input.history, seq);
	ft_printf("%d %d", seq.count, input.history.count);
	shinput_destruct(&input);
	FREE_TESTS();
}
