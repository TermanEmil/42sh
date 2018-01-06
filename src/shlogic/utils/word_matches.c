#include "shlogic.h"
#include "regex_tools.h"

/*
** Check if the given word keys match patern.
*/

t_bool			word_matches(const t_lst_inkey *word_keys, t_rostr patern)
{
	t_str		word_str;
	t_bool		result;

	if ((word_str = word_to_str(word_keys)) == NULL)
		ft_err_mem(TRUE);

	result = regex_mini_match(patern, word_str);
	free(word_str);
	return result;	
}
