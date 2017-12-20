#ifndef SHLOGIC_H
# define SHLOGIC_H

# include "listlib.h"
# include "shinput.h"

typedef struct s_shlogic	t_shlogic;
typedef struct s_logic_vars	t_logic_vars;

/*
** A list of list of t_sh_inkeys.
** First key from the first word:
** (*LCONT((*LCONT(words, t_lst_inkey**)), t_sh_inkey**)
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

void				del_lst_of_words(t_lst_words *words);

#endif
