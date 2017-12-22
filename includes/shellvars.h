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

struct		s_shvars
{
	t_hashtab	*env;
	t_hashtab	*local;
};

t_shvars	shvars_construct(const char **envp);
void		shvars_destroy(t_shvars *shvars);

#endif