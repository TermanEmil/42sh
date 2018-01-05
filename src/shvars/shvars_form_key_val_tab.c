#include "shellvars.h"

t_str	*shvars_form_key_val_tab(const t_hashtab *htab)
{
	t_str		*result;
	t_str		buf;
	ssize_t		iter_i;
	t_hashpair	*pair;
	int			i;

	if ((result = malloc((htab_count(htab) + 1) * sizeof(t_str))) == NULL)
		ft_err_mem(TRUE);

	iter_i = 0;
	i = 0;
	do
	{
		pair = htab_get_next_pair_iter(
			(t_hashtab*)htab, new_hashmem(NULL, 0), &iter_i, NULL);

		if (pair == NULL)
			break;

		buf = ft_strmegajoin(3, pair->key.mem, "=", pair->val.mem);
		if (buf == NULL)
			ft_err_mem(TRUE);
		result[i++] = buf;
	} while (pair != NULL);
	result[i] = NULL;
	return result;
}
