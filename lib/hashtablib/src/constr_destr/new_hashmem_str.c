#include "hashtablib.h"

t_hashmem	new_hashmem_str(char * const str)
{
	return (new_hashmem(str, ft_strlen(str) + 1));
}

t_hashmem	new_hashmem_str_cp(char const *str)
{
	return (new_hashmem_str(ft_strdup(str)));
}