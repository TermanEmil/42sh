#include "shlogic.h"
#include <regex.h>

/*
** It includes all kinds of redirections or ';|'.
*/

static const t_rostr	g_regex_redir_patern_ =
	"("
	"[0-9]*[><]+|"
	"[0-9]*[><]+&[0-9]+|"
	"[0-9]*[><]+&-|"
	";|"
	"\\||"
	"\\|&)";

/*
** Process the case when a match has been found and it's not inside of any kind
** of 'parenthesises': ()[]{}\`'" etc.
*/

static void		_process_base_case(
					t_lst_words	**result,
					const t_lst_inkey *word_keys,
					int match_i,
					int len_of_match,
					t_lst_inkey **word_buf)
{
	t_lst_inkey	*to_add;

	to_add = NULL;
	if (word_buf != NULL)
	{
		to_add = *word_buf;
		*word_buf = NULL;
	}
	
	if (match_i != 0)
	{
		ft_lstadd(&to_add, ft_lst_cpy_range(word_keys, 0,
			match_i - 1, (t_lcpy_cont*)&std_mem_assign));
	}

	if (to_add)
		ft_lstadd(result, ft_lstnew_nocpy(to_add, sizeof(to_add)));

	ft_lstadd(result, ft_lstnew_nocpy(ft_lst_cpy_range(word_keys, match_i,
			match_i + len_of_match - 1, (t_lcpy_cont*)&std_mem_assign),
		sizeof(t_list*)));
}

/*
** If the match isn't inside of anything that cancel it's propreties, then it's
** processed as a base case, otherwise add to word_buff all keys until the end
** of the match.
** After that, more the word_keys pointer to the end of the match and return the
** end of the match in bytes (for str).
**
** Warning: keep in mind that there may be unicode!
*/

static int		_process_regex_match(
					t_lst_words **result,
					t_lst_inkey **word_keys,
					t_lst_inkey **word_buf,
					regmatch_t pmatch)
{
	t_lst_inkey	*match;
	int			match_i;
	int			len_of_match;

	match = get_shinkey_at_strlen(*word_keys, pmatch.rm_so);
	match_i = ft_lst_indexof(
		*word_keys, match->content, 0, &std_lst_cont_ptr_cmp);
	len_of_match = pmatch.rm_eo - pmatch.rm_so;

	if (!ft_strchr("\"\'\\`()[]{}", LCONT(match, t_sh_inkey*)->inside_of))
		_process_base_case(result, *word_keys, match_i, len_of_match, word_buf);
	else
	{
		ft_lstadd(word_buf, ft_lst_cpy_range(*word_keys, 0,
			match_i + len_of_match - 1, (t_lcpy_cont*)&std_mem_assign));
	}

	*word_keys = ft_lstget(*word_keys, match_i + len_of_match);
	return (pmatch.rm_eo == 0) ? 1 : pmatch.rm_eo;
}

/*
** To find all redirections or pipes or ';', regex is used.
** While it's not end of string or end or word_keys, try to find a regex match.
*/

static void		_add_words_at_each_regex_match(
					t_lst_words **result,
					t_lst_inkey **word_keys,
					t_lst_inkey **word_buf,
					t_rostr word_str)
{
	int			ret;
	int			i;
	regex_t		regex_patern;
	regmatch_t	pmatch;

	ret = regcomp(&regex_patern, g_regex_redir_patern_, REG_EXTENDED);
	if (ret != 0)
		ft_proj_err("Regex failed at divide_by_redirections (1)", 1);

	i = 0;
	while (word_str[i] && word_keys != NULL)
	{
		ret = regexec(&regex_patern, word_str + i, 1, &pmatch, 0);
		if (ret == 0)
			i += _process_regex_match(result, word_keys, word_buf, pmatch);
		else if (ret == REG_NOMATCH)
			break;
		else
			ft_proj_err("Regex failed at divide_by_redirections (2)", 1);
	}
	regfree(&regex_patern);
}

/*
** Add the remaining keys as a word. If the initial word had no redirections,
** or no pipies or ';', then the whole word will pe added here.
*/

static void		_add_reaming_keys(
					t_lst_words **result,
					const t_lst_inkey *word_keys,
					t_lst_inkey **word_buf)
{
	t_lst_inkey	*to_add;

	to_add = NULL;
	if (word_buf != NULL)
	{
		to_add = *word_buf;
		word_buf = NULL;
	}

	if (word_keys != NULL)
		ft_lstadd(&to_add, ft_lst_full_cpy(
			word_keys,
			(t_lcpy_cont*)&std_mem_assign,
			(t_ldel_func*)&sh_inkey_destruct));

	if (to_add)
		ft_lstadd(result, ft_lstnew_nocpy(to_add, sizeof(to_add)));
}

/*
** Divide the given word (list of keys) by redirections. The given word_keys
** can be freed (only the list structure, not the contents, that is, not the
** t_sh_inkey*-s).
** word_buf is used in case a match was found, but the key is inside of any kind
** of 'parenthesises': ()[]{}\`'" etc. In that case, the keys until the end of
** the match are added to this buffer. If another match has been found, then
** this buf is added to the 'prematch word' and is given NULL value.
*/

t_lst_words		*_divide_word_by_redirections(t_lst_inkey *word_keys)
{
	t_lst_words		*result;
	t_lst_inkey		*word_buf;
	t_str			word_str;

	word_str = word_to_str(word_keys);
	if (word_str == NULL)
		ft_err_mem(1);

	word_buf = NULL;
	result = NULL;
	_add_words_at_each_regex_match(&result, &word_keys, &word_buf, word_str);
	free(word_str);
	_add_reaming_keys(&result, word_keys, &word_buf);
	return result;
}

/*
** Divide the given words, in subwords, where redirections or pipes or ';' are
** found. Each such redirection is put in another word.
** Kinds of redirections it finds:
**  >, >>, <<, <><><>>>><<><>< etc, 131231231>, 1132312>&1312312, 1231231>&-,
**  ;, |.
** The regex rule is specified at the top of the file.
*/

void			divide_by_redirections(t_lst_words **words)
{
	t_lst_words	*result;
	t_lst_words	*word;
	t_lst_inkey	*word_keys;

	result = NULL;
	for (word = *words; word; LTONEXT(word))
	{
		if (word->content == NULL)
			continue;

		word_keys = LCONT(word, t_lst_inkey*);
		ft_lstadd(&result, _divide_word_by_redirections(word_keys));
	}
	del_lst_of_words_not_content(*words);
	*words = result;
}
