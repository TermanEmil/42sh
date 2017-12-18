#include "shell42.h"
#include "ft_key_codes.h"

// static void		add_key_cmd(t_hashtab * const htab, char const * const key,
// 					t_key_cmd_f * const f)
// {
// 	hashtab_add_pair(htab,
// 		new_hashpair_mllc(
// 			new_hashmem_str((char*)key),
// 			new_hashmem(f, sizeof(f))));
// }

static void		add_key_cmd_term(t_hashtab * const htab, t_term_key const keys,
					t_key_cmd_f * const f)
{
	int			i;
	char const	*key_str;

	for (i = 0; keys[i]; i++)
	{
		key_str = term_tgetstr(keys[i]);
		if (key_str == NULL)
			key_str = keys[i];
		hashtab_add_pair(htab,
			new_hashpair_mllc(
				new_hashmem_str_cp((char*)key_str),
				new_hashmem(f, sizeof(f))));
	}
}

void			std_str_print_key(t_hashpair const *pair)
{
	if (pair)
	{
		ft_print_key((char const*)pair->key.mem);
		term_move_cursor_to_left_most();
	}
}

void			shell_init_key_cmds_htab(void)
{
	t_hashtab	*htab;

	htab = new_hashtab(124, &std_mem_del, NULL);
	g_shinput->key_cmds = htab;
	event_global_force_add("at_exit", event_instance_construct(
		(t_handler_f*)&del_hashtab, &g_shinput->key_cmds));
	
	add_key_cmd_term(htab, term_key_left, &key_cmd_arrow_left);
	add_key_cmd_term(htab, term_key_right, &key_cmd_arrow_right);
	add_key_cmd_term(htab, term_key_up, &key_cmd_arrow_up);
	add_key_cmd_term(htab, term_key_down, &key_cmd_arrow_down);
	add_key_cmd_term(htab, term_key_ctrl_left, &key_cmd_ctrl_arrow_left);
	add_key_cmd_term(htab, term_key_ctrl_right, &key_cmd_ctrl_arrow_right);
	add_key_cmd_term(htab, term_key_alt_up, &key_cmd_alt_up);
	add_key_cmd_term(htab, term_key_alt_down, &key_cmd_alt_down);

	add_key_cmd_term(htab, term_key_backspace, &key_cmd_backspace);
	add_key_cmd_term(htab, term_key_home, &key_cmd_home);
	add_key_cmd_term(htab, term_key_end, &key_cmd_end);
	add_key_cmd_term(htab, term_key_enter, &key_cmd_enter);
}
