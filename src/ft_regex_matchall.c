#include "libft.h"
#include "listlib.h"
#include <regex.h>

static int			add_match(
						t_lst_str **matches,
						t_rostr str,
						const regmatch_t *pmatch)
{
	int		size;

	size = pmatch->rm_eo - pmatch->rm_so;
	if (pmatch->rm_eo - pmatch->rm_so == 0)
		ft_lstadd(matches, ft_lstnew("", 1));
	else
		ft_lstadd(matches, ft_lstnew_str_nocpy(
			ft_strndup(str + pmatch->rm_so, size)));
	return (pmatch->rm_eo == 0) ? 1 : pmatch->rm_eo;
}

static t_lst_str	*extract_regex_matches(
						const regex_t *regex_patern,
						t_rostr str,
						int str_flags,
						t_bool verbose)
{
	int			ret;
	regmatch_t	pmatch;
	char		errbuf[124];
	t_lst_str	*matches;

	matches = NULL;
	while (*str)
	{
		ret = regexec(regex_patern, str, 1, &pmatch, str_flags);
		if (ret == 0)
			str += add_match(&matches, str, &pmatch);
		else if (ret == REG_NOMATCH)
			break;
		else
		{
			if (verbose)
			{
				regerror(ret, regex_patern, errbuf, sizeof(errbuf));
				ft_fprintf(STDERR_FILENO, "Regex failed: %s", errbuf);
			}
			ft_lstdel(&matches, &std_mem_del);
			return NULL;
		}
	}
	return matches;
}

/*
** \\([0-9]*[><]\\+\\|[0-9]*[><]*\\&[0-9]*\\|[0-9]*[><]*\\&-\\)
*/

t_lst_str	*ft_regex_matchall(t_rostr patern, t_rostr str,
				int patern_flags, int str_flags, t_bool verbose)
{
	int			ret;
	t_lst_str	*result;	
	regex_t		regex_patern;

	result = NULL;
	ret = regcomp(&regex_patern, patern, patern_flags);
	if (ret != 0)
	{
		if (verbose)
			ft_putendl_fd("Could not compile regex.", STDERR_FILENO);
		ft_lstdel(&result, &std_mem_del);
		return NULL;
	}
	result = extract_regex_matches(&regex_patern, str, str_flags, verbose);
	regfree(&regex_patern);
	return result;
}
