#ifndef SHLOGIC_H
# define SHLOGIC_H

# include "shellvars.h"
# include "listlib.h"
# include "shinput.h"

typedef struct s_shlogic	t_shlogic;
typedef struct s_logic_vars	t_logic_vars;

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

struct				s_shlogic
{
	t_logic_vars	logic_vars;
};

/*
** lst of words
*/

t_lst_words			*extract_words_from_keys(t_lst_inkey const *keys);
t_str				*words_to_argv(t_lst_words *words);
void				del_lst_of_words(t_lst_words *words);

void				process_dollar_values(
						t_lst_words *words, const t_shvars *shvars);

/*
** Utils
*/

void				debug_print_strings(t_str *strings);

#endif
