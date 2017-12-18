#include "shinput.h"

/*
** Finds the length of the meaning in the given sequence.
*/

size_t	input_seq_get_meaning_len(t_shinput_seq const * const seq,
			size_t const starting_with)
{
	size_t		n;
	size_t		i;
	t_lst_inkey	*aux;

	n = 0;
	aux = seq->keys;
	i = 0;
	while (aux)
	{
		if (i >= starting_with)
			n += ft_strlen(sh_inkey_get_meaning(LCONT(aux, t_sh_inkey*)));
		LTONEXT(aux);
		i++;
	}
	return (n);
}
