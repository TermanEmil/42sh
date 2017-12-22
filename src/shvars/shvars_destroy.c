#include "shellvars.h"

void		shvars_destroy(t_shvars *shvars)
{
	if (shvars->env != NULL)
		del_hashtab(&shvars->env);
	if (shvars->local != NULL)
		del_hashtab(&shvars->local);
}
