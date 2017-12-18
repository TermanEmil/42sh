#include "shtests.h"

void	input_history_test_add_pop(void)
{
	t_input_history	history;
	t_shinput_seq	seq;
	char			*out;

	history = input_history_construct();
	history.nb_of_inputs_to_remember = 2;
	seq = shinput_seq_construct();

	ft_printf("%d\n", history.count); //0
	
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("a"), NULL));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("B"), NULL));
	input_history_add_seq(&history, seq);
	ft_printf("%d\n", history.count); //1
	
	ft_bzero(&seq, sizeof(seq));
	
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("c"), NULL));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("D"), NULL));
	input_history_add_seq(&history, seq);
	ft_printf("%d\n", history.count); //2
	
	ft_bzero(&seq, sizeof(seq));
	
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("e"), NULL));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("F"), NULL));
	input_history_add_seq(&history, seq); //2
	
	ft_bzero(&seq, sizeof(seq));
	
	ft_printf("%d\n", history.count);
	history.nb_of_inputs_to_remember = 3;
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("g"), NULL));
	input_seq_add_key(&seq, sh_inkey_construct(ft_strdup("H"), NULL));
	input_history_add_seq(&history, seq); //3
	ft_printf("%d\n", history.count);
	
	out = input_seq_get_meaning(LCONT(history.inputs, t_shinput_seq*));
	ft_putendl(out); //gH
	free(out);
	
	out = input_seq_get_meaning(LCONT(history.inputs->next, t_shinput_seq*));
	ft_putendl(out); //eF
	free(out);
	
	out = input_seq_get_meaning(LCONT(history.inputs->next->next, t_shinput_seq*));
	ft_putendl(out); //cD
	free(out);

	input_history_destruct(&history);
	FREE_TESTS();
}

/*
	0
	1
	2
	2
	3
	gH
	eF
	cD
*/