#include "shlogic.h"
#include <regex.h>

#define __REGEX_FIRST_PART__ "\\(^\\|[ \t\n]\\+\\)"

/*
** It includes all kinds of
*/

static const t_rostr	regex_redir_patern =
	"\\("
	"[0-9]*[><]\\+\\|"
	"[0-9]*[><]\\+\\&[0-9]*" "\\($\\|[ \t\n]\\+\\)" "\\|"
	"[0-9]*[><]\\+\\&-\\|"
	";\\|"
	"|\\)";

/*
** For len = 0, it will return the first key.
*/

t_lst_inkey		*get_shinkey_at_strlen(t_lst_inkey *keys, int len)
{
	for (; keys; LTONEXT(keys))
	{
		if (len <= 0)
			return keys;
		len -= ft_strlen(sh_inkey_get_meaning(LCONT(keys, t_sh_inkey*)));
	}
	ft_proj_err("get_shinkey_at_len_index: invalid len", TRUE);
	return NULL;
}

t_list		*ft_lst_cpy_range(
				const t_list *head, int i1, int i2,
				t_lcpy_cont *f_cpy_cont)
{
	t_list	*result;

	if (i1 > i2 || i1 < 0 || i2 < 0)
		return NULL;
	while (i1 != 0 && head)
	{
		i1--;
		i2--;
		LTONEXT(head);
	}
	result = NULL;
	while (head && i2 >= 0)
	{
		i2--;
		ft_lstadd(&result, ft_lstnew_nocpy(
			f_cpy_cont(head->content, head->content_size),
			head->content_size));
		LTONEXT(head);
	}
	return result;
}

int			ft_lst_indexof(
				const t_list *lst,
				const void *target,
				size_t target_size,
				t_lst_cont_cmp *cmp)
{
	int		i;

	if (cmp == NULL)
		cmp = (t_lst_cont_cmp*)&ft_memcmp;

	i = 0;
	while (lst)
	{
		if (cmp(target, lst->content, target_size, lst->content_size))
			return i;
		i++;
		LTONEXT(lst);
	}
	return -1;
}

/*
	t_lst_inkey	*lst_inkey;
			t_lst_inkey	*tmp;
			int			matching_len;
			int			tmp_i;

			tmp = get_shinkey_at_strlen(word_keys, pmatch.rm_so + index_dif);
			
			ft_printf("\nstr: i = %d|%d-%d '%s'\n",
				i, pmatch.rm_so, pmatch.rm_eo,
				sh_inkey_get_meaning(LCONT(tmp, t_sh_inkey*)));
			term_getch();
		
			tmp_i = ft_lst_indexof(
				word_keys, tmp->content, 0, &std_lst_cont_ptr_cmp);

			matching_len = pmatch.rm_eo - pmatch.rm_so;
			
			if (ft_strchr("\"\'\\`()[]{}", LCONT(tmp, t_sh_inkey*)->inside_of))
			{
				i++;
				continue;
			}
			if (tmp != word_keys)
			{
				ft_lstadd(&result,
					ft_lstnew_nocpy(ft_lst_cpy_range(word_keys, 0,
						pmatch.rm_so - 1,
						(t_lcpy_cont*)&sh_inkey_cpy_construct_ptr),
					sizeof(t_list*)));
			}

			ft_lstadd(&result,
				ft_lstnew_nocpy(
					ft_lst_cpy_range(word_keys, tmp_i, pmatch.rm_eo - 1,
						(t_lcpy_cont*)&sh_inkey_cpy_construct_ptr),
					sizeof(t_list*)));
			word_keys = ft_lstget(word_keys, pmatch.rm_eo);
			index_dif = 0;
			// else
				// index_dif = pmatch.rm_eo;
			// word_keys = ft_lstget(word_keys, pmatch.rm_eo);	
			i += ((pmatch.rm_eo == 0) ? 1 : (pmatch.rm_eo));
*/

t_lst_words	*divide_word_by_redirections(t_lst_inkey *word_keys)
{
	t_lst_words			*result;
	t_str				word_str;

	result = NULL;
	word_str = word_to_str(word_keys);
	if (word_str == NULL)
		ft_err_mem(1);
	
	int			ret;
	regex_t		regex_patern;
	regmatch_t	pmatch;
	int			i;
	int			index_dif;

	ret = regcomp(&regex_patern, regex_redir_patern, 0);
	if (ret != 0)
		ft_proj_err("Regex failed at divide_by_redirections (1)", 1);

	index_dif = 0;
	i = 0;
	while (word_str[i] && word_keys != NULL)
	{
		ret = regexec(&regex_patern, word_str + i, 1, &pmatch, 0);
		if (ret == 0)
		{
			t_lst_inkey	*start_of_match;
			int			index_of_first_matching_key;
			t_sh_inkey	*start_of_match_key;
			int len_of_matching;

			start_of_match = get_shinkey_at_strlen(word_keys,
				pmatch.rm_so + index_dif);
			index_of_first_matching_key = ft_lst_indexof(
				word_keys, start_of_match->content, 0, &std_lst_cont_ptr_cmp);
			start_of_match_key = LCONT(start_of_match, t_sh_inkey*);

			len_of_matching	= pmatch.rm_eo - pmatch.rm_so;

			ft_printf("\n'%s' %d|%d|%d-%d len:%d '%s'\n",
				sh_inkey_get_meaning(start_of_match_key),
				i, index_of_first_matching_key, pmatch.rm_so, pmatch.rm_eo,
				len_of_matching, word_str + i);
			term_getch();

			if (!ft_strchr("\"\'\\`()[]{}", start_of_match_key->inside_of))
			{
				if (start_of_match != word_keys)
				{
					ft_lstadd(&result,
						ft_lstnew_nocpy(ft_lst_cpy_range(word_keys, 0,
							index_of_first_matching_key - 1,
							(t_lcpy_cont*)&sh_inkey_cpy_construct_ptr),
						sizeof(t_list*)));
				}

				ft_lstadd(&result,
					ft_lstnew_nocpy(
						ft_lst_cpy_range(word_keys,
							index_of_first_matching_key,
							index_of_first_matching_key + len_of_matching - 1,
							(t_lcpy_cont*)&sh_inkey_cpy_construct_ptr),
						sizeof(t_list*)));

				word_keys = ft_lstget(word_keys,
					index_of_first_matching_key + len_of_matching);
				
				index_dif = 0;
			}
			else
				index_dif = pmatch.rm_eo;
			i += ((pmatch.rm_eo == 0) ? 1 : (pmatch.rm_eo));
		}
		else if (ret == REG_NOMATCH)
			break;
		else
			ft_proj_err("Regex failed at divide_by_redirections (2)", 1);
	}

	free(word_str);
	regfree(&regex_patern);

	if (word_keys != NULL)
	{
		t_lst_inkey	*cpy = ft_lst_full_cpy(
			word_keys,
			(t_lcpy_cont*)&sh_inkey_cpy_construct_ptr,
			(t_ldel_func*)&sh_inkey_destruct);

		ft_lstadd(&result, ft_lstnew_nocpy(cpy, sizeof(cpy)));
	}

	return result;
}

t_lst_words	*divide_by_redirections(const t_lst_words *words)
{
	t_lst_words	*result;
	t_lst_inkey	*word_keys;

	result = NULL;
	for (; words; LTONEXT(words))
	{
		if (words->content == NULL)
			continue;
		word_keys = LCONT(words, t_lst_inkey*);
		ft_lstadd(&result,
			divide_word_by_redirections(word_keys));
		// ft_lstdel(&word_keys, (t_ldel_func*)&sh_inkey_destruct);
	}
	return result;
}
