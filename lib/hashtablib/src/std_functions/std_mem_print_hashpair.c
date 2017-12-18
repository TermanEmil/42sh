#include "hashtablib.h"
#include "ft_errors.h"

static void	print_memory(char const *mem, size_t const size)
{
	size_t	i;
	int		n;

	n = 0;
	i = 0;
	while (i < size)
	{
		if (n == 8)
			ft_putchar(' ');
		if (ft_isprint(mem[i]))
			ft_putchar(mem[i]);
		else
			ft_putchar('.');
		i++;
		n++;
	}
}

/*
** Prints the memory of the key and val: if it's a printable character,
** it prints the char, else, a dot is printed. [..qwe... .qer..]: [.weqr.]
** A space is put between every eight bytes.
*/

void		std_mem_print_hashpair(t_hashpair const *pair)
{
	if (pair != NULL)
	{
		if (pair == (t_hashpair*)&g_htab_dummy)
		{
			ft_putendl("[Dummy]");
			return;
		}
		ft_putchar('[');
		print_memory((char*)(pair->key.mem), pair->key.size);
		ft_putstr("]: [");
		print_memory((char*)(pair->val.mem), pair->val.size);
		ft_putstr("]\n");
	}
}
