#include "listlib.h"

static inline size_t	get_total_str_size(
							t_list const *list,
							size_t delim_len,
							int n)
{
	size_t	size;

	size = 0;
	for (; list && n > 0; LTONEXT(list), n--)
		if (list->content != NULL)
			size += ft_strlen(LSTR(list)) + delim_len;
	if (size > 0)
		size -= delim_len;
	return size + 1;
}

/*
** Join n elements from the given list in a string.
*/

t_str					ft_lst_njoin(
							t_list const *list,
							t_rostr (*get_str)(const void*, size_t),
							t_rostr delim,
							int n)
{
	t_str			result;

	result = ft_strnew(get_total_str_size(list,
		(delim == NULL) ? 0 : ft_strlen(delim), n));
	if (result == NULL)
		return NULL;

	for (; list && n > 0; LTONEXT(list), n--)
		if (list->content != NULL)
		{
			ft_strcat(result, get_str(list->content, list->content_size));
			if (delim != NULL && !L_IS_LAST(list))
				ft_strcat(result, delim);
		}
	return result;
}
