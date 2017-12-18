#include "libft.h"

static inline t_bool	chars_are_folow_uni_len(
							const unsigned char *chars,
							size_t const required_len)
{
	size_t	i;

	for (i = 0; i < required_len; i++)
	{
		if ((chars[i] >> 6) != 0x2)
			return (FALSE);	
	}
	return (TRUE);
}

/*
** Returns the first (starting from key[0]) utf8 character. NULL if it's not one
*/

char const			*utf8_get_first(unsigned char const * const key)
{
	static char		buf[5];
	size_t			required_len;

	if (key[0] >> 7 == 0)
		required_len = 1;
	else if (key[0] >> 5 == 0x6)
		required_len = 2;
	else if (key[0] >> 4 == 0xE)
		required_len = 3;
	else if (key[0] >> 5 == 0x1E)
		required_len = 4;
	else
		return (NULL);
	if (chars_are_folow_uni_len(key + 1, required_len - 1))
	{
		ft_strncpy(buf, (char*)key, required_len);
		buf[required_len] = 0;
		return (buf);
	}
	else
		return (NULL);	
}
