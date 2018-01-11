#include "shlogic.h"
#include <sys/types.h>
#include <dirent.h>
#include "regex_tools.h"

static t_str	find_cmd_in_specific_path_(
					t_rostr path,
					t_rostr cmd,
					t_bool (*cmp_f)(t_rostr, t_rostr))
{
	DIR				*dir_path;
	struct dirent	*dir_buf;
	t_str			file_path;

	if ((dir_path = opendir(path)) == NULL)
	{
		errno = 0;
		return NULL;
	}
	file_path = NULL;
	while ((dir_buf = readdir(dir_path)) != NULL)
	{
		if (cmp_f(cmd, dir_buf->d_name))
		{
			file_path = ft_strmegajoin(3, path, "/", dir_buf->d_name);
			if (file_path == NULL)
				ft_err_mem(TRUE);
			break;
		}
	}
	errno = 0;
	closedir(dir_path);
	return file_path;
}

t_str			find_cmd_in_env_path(
					t_rostr cmd,
					const t_shvars *shvars,
					t_bool is_regex_patern)
{
	t_rostr	path_val;
	t_str	*paths;
	int		i;
	t_str	result;

	path_val = htab_get_strval(shvars->env, new_hashmem_str("PATH"));
	if (path_val == NULL)
		return NULL;

	if ((paths = ft_strsplit(path_val, ':')) == NULL)
		ft_err_mem(TRUE);

	for (i = 0, result = NULL; result == NULL && paths[i]; i++)
		result = find_cmd_in_specific_path_(paths[i], cmd,
			(is_regex_patern) ? &regex_mini_match : &ft_strequ);

	ft_free_bidimens(paths);
	return result;
}
