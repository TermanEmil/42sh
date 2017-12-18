#ifndef UNITTEST_H
# define UNITTEST_H

# include "listlib.h"

# define TEST_FAIL	-42
# define TEST_SUCC	42
# define TEST_COREDUMP 2
# define LTEST(list_cell) LCONT(list_cell, t_unittest*)

/*
** When running valgrind, you'll see that all subproecesses have memory leaks,
** that's because they don't free the memory from "add_test" from the beginning
** of the program, so it's fine with that.
** In each child process has (n_tests * 2) leaks
*/

typedef void (func_utest)(void);

typedef struct	s_unittest
{
	func_utest	*f;
	char const	*expected_out;
	char const	*f_name;
}				t_unittest;

typedef struct	s_ltest_rs
{
	int			fails;
	int			seg_faults;
	int			core_dump;
	int			successes;
}				t_ltest_rs;

t_unittest		*new_test(func_utest *test, char const *out, char const *fname);
void			get_func_out(func_utest *f, char * buf, ssize_t buf_len,
					int * child_status);
int				run_test(t_unittest * utest, char * buf, ssize_t buf_len);
t_ltest_rs		run_listed_tests(t_list * tests, char * buf, ssize_t buf_len);
void			test_print_final_results(t_ltest_rs result);
void			add_test(t_list ** head, t_unittest * new_test);

#endif