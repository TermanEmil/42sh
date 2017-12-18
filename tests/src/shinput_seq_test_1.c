#include "shtests.h"

static void		insert_sum_shit(t_shinput_seq * const seq)
{
	input_seq_add_key(seq, sh_inkey_construct(ft_strdup("^["), ft_strdup("\033")));
	input_seq_add_key(seq, sh_inkey_construct(ft_strdup("a"), NULL));
	input_seq_add_key(seq, sh_inkey_construct(ft_strdup("B"), NULL));
	input_seq_insert_key(seq, sh_inkey_construct(ft_strdup("^["), ft_strdup("\033")), 0);
	input_seq_insert_key(seq, sh_inkey_construct(ft_strdup("^["), ft_strdup("\033")), 1);
	input_seq_insert_key(seq, sh_inkey_construct(ft_strdup("^["), ft_strdup("\033")), 4);
}

static void		delete_sum_shit(t_shinput_seq * const seq)
{
 	input_seq_rm_key_at(seq, 0);
	input_seq_rm_key_at(seq, 4);
}

void	shinput_seq_test_1(void)
{
	t_shinput_seq	seq;
	char			*tmp;

	seq = shinput_seq_construct();
	insert_sum_shit(&seq);
	delete_sum_shit(&seq);
	tmp = input_seq_get_displayed(&seq);
	ft_putstr(tmp);
	free(tmp);
	tmp = input_seq_get_meaning(&seq);
	ft_printf(" %s\n%d\n", tmp, seq.count);
	free(tmp);
	ft_lstdel(&seq.keys, (t_ldel_func*)&sh_inkey_destruct);
	FREE_TESTS();
}
