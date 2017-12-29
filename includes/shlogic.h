#ifndef SHLOGIC_H
# define SHLOGIC_H

# include "shellvars.h"
# include "listlib.h"
# include "shinput.h"

typedef struct s_logic_vars		t_logic_vars;
typedef struct s_ft_system_ret	t_ft_system_ret;

/*
** A list of list of t_sh_inkeys.
** First key from the first word:
** LCONT((LCONT(words, t_list*)), t_sh_inkey*)
*/

typedef t_list		t_lst_words;

struct				s_logic_vars
{
	t_hashtab		*env;
	t_hashtab		*vars;
};

/*
** Destructors
*/

void				del_lst_of_words(t_lst_words *words);
void				del_lst_of_words_not_content(t_lst_words *words);

/*
** lst of words
*/

t_lst_words			*extract_words_from_keys(t_lst_inkey const *keys);
void				process_dollar_values(
						t_lst_words *words, const t_shvars *shvars);
void				divide_by_redirections(t_lst_words **words);

/*
** Word processing (both in same file).
*/

t_str				word_to_display_str(const t_lst_inkey *keys);
t_str				*words_to_argv(t_lst_words *words);

/*
** Tilde
*/

void				proceess_tilde(t_lst_words	*words,
						const t_shvars *shvars);
t_lst_inkey			*process_tilde_in_word(const t_lst_inkey *word,
						const t_shvars *shvars);
t_str				get_tilde_prefix(const t_lst_inkey *keys, int *len);
t_str				get_tilde_value(t_rostr tilde_prefix,
						const t_shvars *shvars);
/*
** Utils
*/

void				debug_print_strings(t_str *strings);
t_str				extract_var_name_from_keys(const t_lst_inkey *keys);
t_str				word_to_str(const t_lst_inkey *keys);

#endif
