#include "shlogic.h"

void	check_for_valid_args_(const t_str *argv)
{
	if (argv[1] != NULL)
		ft_proj_err("execute_cmd_set_local_var accepts only one arg", TRUE);
	if (!cmd_is_set_var(argv[0]))
		ft_proj_err("execute_cmd_set_local_var was given an invalid arg", TRUE);
}

int		execute_cmd_set_local_var(t_cmd_env *cmd_env)
{
	int		ret;
	t_str	key;
	t_str	val;
	t_rostr	start_of_eq;

	check_for_valid_args_(cmd_env->argv);
	start_of_eq = ft_strchr(cmd_env->argv[0], '=');
	if (start_of_eq == NULL)
		ft_proj_err("execute_cmd_set_local_var failed to find `='", TRUE);

	if (!(key = ft_strndup(cmd_env->argv[0], start_of_eq - cmd_env->argv[0])))
		ft_err_mem(TRUE);
	if ((val = ft_strdup(start_of_eq + 1)) == NULL)
		ft_err_mem(TRUE);

	ret = htab_set_pair(cmd_env->shvars->local,
		new_hashpair(new_hashmem_str(key), new_hashmem_str(val)));
	free(key);
	free(val);
	if (ret != 0)
		ft_err_erno(errno, FALSE);

	return ret;
}
