#include "shlogic.h"
#include "regex_tools.h"
#include <regex.h>

static void	process_word_(
				t_lst_inkey *word,
				const regex_t *regex_patern,
				t_grps_wrds **result,
				t_lst_words	**buf)
{
	int		ret;
	t_str	argv;

	argv = word_to_str(word);
	if (argv == NULL)
		ft_err_mem(1);

	ret = regexec(regex_patern, argv, 0, NULL, 0);
	if (ret == 0)
	{
		if (*buf != NULL)
			ft_lstadd(result, ft_lstnew_nocpy(*buf, sizeof(*buf)));
		*buf = ft_lstnew_nocpy(word, sizeof(word));
		ft_lstadd(result, ft_lstnew_nocpy(*buf, sizeof(*buf)));
		*buf = NULL;
	}
	else if (ret == REG_NOMATCH)
		ft_lstadd(buf, ft_lstnew_nocpy(word, sizeof(word)));
	else
		regex_proj_error(regex_patern, ret, 2);

	free(argv);
}

/*
** Group words by the given regex patern delim. The delims are also included.
*/

t_grps_wrds	*group_words_by_delim(t_lst_words *words, t_rostr delim_reg_patern)
{
	t_lst_words	*buf;
	t_grps_wrds	*result;
	regex_t		regex_patern;
	int			ret;

	if ((ret = regcomp(&regex_patern, delim_reg_patern, REG_EXTENDED)) != 0)
		regex_proj_error(&regex_patern, ret, 1);

	for (result = NULL, buf = NULL; words; LTONEXT(words))
		process_word_(LCONT(words, t_lst_inkey*), &regex_patern, &result, &buf);

	if (buf != NULL)
		ft_lstadd(&result, ft_lstnew_nocpy(buf, sizeof(buf)));

	regfree(&regex_patern);
	return result;
}
