#include <string.h>

size_t	ft_hash(void const *key, size_t const len)
{
	size_t			hash;
	size_t			i;
	unsigned char	*c_key;

	c_key = (unsigned char*)key;
	i = 0;
	hash = 0;
	while (i < len)
	{
		hash += c_key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
		i++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
    return (hash);
}
