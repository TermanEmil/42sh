#include "shellvars.h"

static inline t_hashpair	*get_envp_hashpair(t_rostr str)
{
	t_hashpair	*hashpair;
	t_str		key;
	t_str		val;
	char		*eq_ptr;

	eq_ptr = ft_strchr(str, '=');
	if (eq_ptr == NULL)
		ft_proj_err("Env reading: no equal symbol could be found", TRUE);

	key = ft_strnew(eq_ptr - str);
	if (key == NULL)
		ft_err_mem(TRUE);
	ft_strncpy(key, str, eq_ptr - str);

	val = ft_strdup(eq_ptr + 1);
	if (val == NULL)
		ft_err_mem(TRUE);

	hashpair = new_hashpair_mllc(
		new_hashmem_str(key), new_hashmem_str(val));
	if (hashpair == NULL)
		ft_err_mem(TRUE);
	return hashpair;
}

t_shvars					shvars_construct(const char **envp)
{
	t_shvars	shvars;

	shvars.env = new_hashtab(
		2 * ft_tab_len((const void**)envp), &std_mem_del, &std_mem_del);
	shvars.local = new_hashtab(0, &std_mem_del, &std_mem_del);

	for (; *envp; envp++)
		hashtab_add_pair(shvars.env, get_envp_hashpair(*envp));
	return shvars;
}
