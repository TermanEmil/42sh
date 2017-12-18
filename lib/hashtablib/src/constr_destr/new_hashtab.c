#include "hashtablib.h"
#include "ft_errors.h"

static void		init_default_hashtabl_vals(t_hashtab * const htab)
{
	htab->cmp_f = &std_htab_mem_cmp;
	htab->hash_f = &ft_hash;
	htab->hashcol_f = &hash_linear_probing_method;
}

static void		init_hashtab(t_hashtab * const htab)
{
	init_default_hashtabl_vals(htab);
	htab->free_cells = htab->tablen;
}

t_hashtab		*new_hashtab(size_t const tablen,
					t_del_mem_f * const kdel, t_del_mem_f * const vdel)
{
	t_hashtab	*result;
	size_t		i;

	result = (t_hashtab*)malloc(sizeof(t_hashtab));
	if (result == NULL)
		ft_err_mem(ERR_EXIT_PROG);
	if (tablen > 0)
	{
		result->tab = (t_hashpair**)malloc(sizeof(t_hashtab*) * tablen);
		if (result->tab == NULL)
			ft_err_mem(ERR_EXIT_PROG);
		i = 0;
		while (i < tablen)
		{
			result->tab[i] = NULL;
			i++;
		}
	}
	else
		result->tab = NULL;
	result->tablen = tablen;
	result->kdel = kdel;
	result->vdel = vdel;
	init_hashtab(result);
	return (result);
}
