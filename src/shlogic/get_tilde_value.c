#include "shlogic.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/*
** Get a fresh string of the tilde value.
** ~root -> /root
** ~ -> $HOME or, if it's unset,
*/

t_str			get_tilde_value(
								t_rostr tilde_prefix,
								const t_shvars *shvars)
{
	t_str			result;
	struct passwd 	*buf_passwd;

	if (ft_strequ(tilde_prefix, ""))
	{
		result = htab_get_strval(shvars->env, new_hashmem_str("HOME"));
		if (result != NULL)
			result = ft_strdup(result);
		else
			result = ft_strdup(getpwuid(getuid())->pw_dir);
	}
	else
	{
		INTERPT_RETRY(buf_passwd = getpwnam(tilde_prefix));
		if (buf_passwd == NULL)
			result = NULL;
		else
			result = ft_strdup(buf_passwd->pw_dir);
	}

	return result;
}
