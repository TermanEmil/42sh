#ifndef SHELL42_H
# define SHELL42_H

# include <stdio.h>
# include "libft.h"
# include "listlib.h"
# include "ft_errors.h"
# include "ft_colors.h"
# include "short_named_types.h"
# include "shinput.h"
# include "termlib.h"
# include "eventlib.h"
# include "hashtablib.h"
# include "shlogic.h"
# include "shellvars.h"

# define DEFAULT_PROMPT "[42sh]$>"

typedef struct s_shdata			t_shdata;

extern t_shdata		g_shdata;

struct				s_shdata
{
	char			prompt[36];
	t_shinput		input;
	t_shvars		shvars;
};

/*
** shdata: get, set
*/

char const			*shell_get_prompt(void);

/*
** Signals
*/

void				listen_to_signals(void);

/*
** Initializers
*/

void				init_shell(const char **envp);
void				init_sh_events(void);

/*
** Constructors
*/

t_shdata			shdata_construct(void);

/*
** Destructors
*/

void				shdata_destruct(t_shdata *target);

/*
** Utils
*/

t_lst_str			*ft_regex_matchall(t_rostr patern, t_rostr str,
						int patern_flags, int str_flags, t_bool verbose);


#endif
