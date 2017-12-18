char const	*ft_char_to_str(char const c)
{
	static char	buf[2];

	buf[0] = c;
	buf[1] = 0;
	return (buf);
}
