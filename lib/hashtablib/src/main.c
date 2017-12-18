#include "hashtablib.h"
#include "ft_errors.h"

int		main(void)
{
	t_hashtab	*a;

	a = new_hashtab(100, &std_mem_del, &std_mem_del);
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("emil"),
			new_hashmem_str_cp("C")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("Valera"),
			new_hashmem_str_cp("Dasa")));
	hashtab_add_pair(a,
		new_hashpair_mllc(
			new_hashmem_str_cp("Sergiu"),
			new_hashmem_str_cp("Trafka")));
	std_str_print_hashpair(get_hashpair(a, new_hashmem_str("Sergiu")));
	htab_rehash(a, 100);
	ft_putnewl();
	htab_iter(a, &std_str_print_hashpair);
	htab_rehash(a, 100);
	ft_putnewl();
	htab_iter(a, &std_mem_print_hashpair);
	del_hashtab(&a);
	return (0);
}