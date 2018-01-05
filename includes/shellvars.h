#ifndef SHELLVARS_H
# define SHELLVARS_H

# include <stdio.h>
# include <unistd.h>
# include "libft.h"
# include "listlib.h"
# include "hashtablib.h"
# include "ft_errors.h"
# include "termlib.h"
# include "eventlib.h"

# include "shinput.h"

typedef struct s_shvars	t_shvars;

struct			s_shvars
{
	t_str_htab	*env;
	t_str_htab	*local;
};

t_shvars		shvars_construct(const char **envp);
void			shvars_destroy(t_shvars *shvars);
t_str			*shvars_form_key_val_tab(const t_hashtab *htab);

#endif