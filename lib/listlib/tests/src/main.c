#include "listlib.h"
#include "unittest.h"

#define TEST_2_RES "str--\nstr1\nstr2\nstr3\nstr-\nstr4\n\nstr4\nstr-\nstr3\nstr2\nstr1\nstr--\n"
#define TEST_INSERT "added_3\nadded_2\nadded_1\nstr11\nadded_3\nadded_2\nadded_1\nstr10\nstr9\nstr8\nstr7\nstr6\nstr5\nstr4\nstr3\nstr2\nadded_3\nadded_2\nadded_1\nstr1\nadded_3\nadded_2\nadded_1\n\nadded_1\nadded_2\nadded_3\nstr1\nadded_1\nadded_2\nadded_3\nstr2\nstr3\nstr4\nstr5\nstr6\nstr7\nstr8\nstr9\nstr10\nadded_1\nadded_2\nadded_3\nstr11\nadded_1\nadded_2\nadded_3\n"

#define FREE_TESTS() ft_lstdel(&g_tests, &std_mem_del)

t_list	*g_tests;

void	event_exit(int status)
{
	exit(status);
}

void	test_1(void)
{
	t_list * head;

	head = NULL;
	ft_lstadd(&head, ft_lstnew("str1", 10));
	ft_lstadd(&head, ft_lstnew("str2", 10));
	ft_lstadd(&head, ft_lstnew("str3", 10));
	ft_lstadd(&head, ft_lstnew("str4", 10));
	ft_lstadd(&head, ft_lstnew("str5", 10));
	ft_lstadd(&head, ft_lstnew("str6", 10));
	ft_lstadd(&head, ft_lstnew("str7", 10));
	ft_lstpop_front(&head, &std_mem_del);
	ft_lstpop_back(&head, &std_mem_del);
	ft_lstpop_back(&head, &std_mem_del);
	ft_lstpop_back(&head, &std_mem_del);
	ft_lstpop_back(&head, &std_mem_del);
	ft_lstiter(head, CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_putnewl();
	ft_lst_rev_iter(ft_lstget(head, 1), CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_lstdel(&head, &std_mem_del);
	FREE_TESTS();
}

void	test_2(void)
{
	t_list * head;

	head = NULL;
	ft_lst_push_front(&head, ft_lstnew("str1", 10));
	ft_lst_push_front(&head, ft_lstnew("str2", 10));
	ft_lst_push_front(&head, ft_lstnew("str3", 10));
	ft_lstinsert(&head, 0, ft_lstnew("str4", 10), NULL);
	ft_lstinsert(&head, 1, ft_lstnew("str-", 10), NULL);
	ft_lstinsert(&head, 5, ft_lstnew("str--", 10), NULL);

	ft_lst_rev_iter(ft_lstget(head, 5), CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_putnewl();
	ft_lstiter(head, CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_lstdel(&head, &std_mem_del);
	FREE_TESTS();
}

void	test_3(void)
{
	t_list * head;

	head = NULL;
	ft_lstadd(&head, ft_lstnew("str1", 10));//
	ft_lstadd(&head, ft_lstnew("str2", 10));//
	ft_lstadd(&head, ft_lstnew("str3", 10));//
	ft_lstadd(&head, ft_lstnew("str4", 10));
	ft_lstadd(&head, ft_lstnew("str5", 10));//
	ft_lstadd(&head, ft_lstnew("str6", 10));
	ft_lstadd(&head, ft_lstnew("str7", 10));//
	
	ft_lstrm(&head, ft_lstget(head, 0), &std_mem_del);
	ft_lstrm(&head, ft_lstget(head, 1), &std_mem_del);
	// ft_lstrm(&head, ft_lstget(head, 6), &std_mem_del);
	ft_lstrm_at(&head, 2, &std_mem_del);
	ft_lstrm_at(&head, 0, &std_mem_del);
	ft_lstrm_at(&head, 2, &std_mem_del);

	ft_lst_rev_iter(ft_lstget(head, 1), CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_putnewl();
	ft_lstiter(head, CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_lstdel(&head, &std_mem_del);
	FREE_TESTS();
}

void	test_insert_range(void)
{
	t_list * head;
	t_list * to_add;

	head = NULL;
	ft_lstadd(&head, ft_lstnew("str1", 10));
	ft_lstadd(&head, ft_lstnew("str2", 10));
	ft_lstadd(&head, ft_lstnew("str3", 10));
	ft_lstadd(&head, ft_lstnew("str4", 10));
	ft_lstadd(&head, ft_lstnew("str5", 10));
	ft_lstadd(&head, ft_lstnew("str6", 10));
	ft_lstadd(&head, ft_lstnew("str7", 10));
	ft_lstadd(&head, ft_lstnew("str8", 10));
	ft_lstadd(&head, ft_lstnew("str9", 10));
	ft_lstadd(&head, ft_lstnew("str10", 10));
	ft_lstadd(&head, ft_lstnew("str11", 10));

	to_add = NULL;
	ft_lstadd(&to_add, ft_lstnew("added_1", 10));
	ft_lstadd(&to_add, ft_lstnew("added_2", 10));
	ft_lstadd(&to_add, ft_lstnew("added_3", 10));

	t_list *cpy1 = ft_lst_full_cpy(to_add);
	t_list *cpy2 = ft_lst_full_cpy(to_add);
	t_list *cpy3 = ft_lst_full_cpy(to_add);

	ft_lst_insert_range(&head, 0, to_add);
	ft_lst_insert_range(&head, 4, cpy1);
	ft_lst_insert_range(&head, ft_lstlen(head), cpy2);
	ft_lst_insert_range(&head, ft_lstlen(head) - 4, cpy3);

	ft_lst_rev_iter(ft_lst_get_last(head), CAST(&ft_lstprint_str, void (*)(t_list *)));
	ft_putnewl();
	ft_lstiter(head, CAST(&ft_lstprint_str, void (*)(t_list *)));

	ft_lstdel(&head, &std_mem_del);
	FREE_TESTS();
}

int		main()
{
	char	buf[1024];

	g_tests = NULL;
	add_test(&g_tests, new_test(&test_1, "str2\nstr3\n\nstr3\nstr2\n", "test_1"));
	add_test(&g_tests, new_test(&test_2, TEST_2_RES, "test_2"));
	add_test(&g_tests, new_test(&test_3, "str6\nstr4\n\nstr4\nstr6\n", "test_3"));
	add_test(&g_tests, new_test(&test_insert_range, TEST_INSERT, "test_insert_range"));
	test_print_final_results(run_listed_tests(g_tests, buf, sizeof(buf)));
	FREE_TESTS();
	return (0);
}