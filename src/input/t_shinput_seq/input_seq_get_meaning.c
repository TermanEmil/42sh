#include "shinput.h"

/*
** Returns a fresh string with the meaning of the sequence.
*/

char	*input_seq_get_meaning(t_shinput_seq const * const seq,
			size_t const starting_with)
{
	char		*result;
	size_t		i;
	t_lst_inkey	*aux;

	result = ft_strnew(input_seq_get_meaning_len(seq, starting_with));
	if (result == NULL)
		ft_err_mem(1);
	aux = seq->keys;
	i = 0;
	while (aux)
	{
		if (i >= starting_with)
			ft_strcat(result, sh_inkey_get_meaning(LCONT(aux, t_sh_inkey*)));
		LTONEXT(aux);
		i++;
	}
	return (result);
}
