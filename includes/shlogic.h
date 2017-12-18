#ifndef SHLOGIC_H
# define SHLOGIC_H

# include "listlib.h"
# include "shinput.h"

typedef struct s_shlogic	t_shlogic;
typedef struct s_logic_vars	t_logic_vars;

/*
** A list of list of t_sh_inkeys
*/

typedef t_list				t_lst_words;

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

t_str				*lst_of_words_to_argv(t_lst_words const *lst_of_words);
void				lst_of_words_del(t_lst_words *lst_of_words);

#endif
