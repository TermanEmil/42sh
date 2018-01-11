#include "shell42.h"
#include "ft_key_codes.h"

static void		add_key_cmd_term_(t_hashtab * const htab, t_term_key const keys,
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

void			shell_init_key_cmds_htab(void)
{
	t_hashtab	*htab;

	htab = new_hashtab(124, &std_mem_del, NULL);
	g_shinput->key_cmds = htab;
	
	add_key_cmd_term_(htab, term_key_left, &key_cmd_arrow_left);
	add_key_cmd_term_(htab, term_key_right, &key_cmd_arrow_right);
	add_key_cmd_term_(htab, term_key_up, &key_cmd_arrow_up);
	add_key_cmd_term_(htab, term_key_down, &key_cmd_arrow_down);
	add_key_cmd_term_(htab, term_key_ctrl_left, &key_cmd_ctrl_arrow_left);
	add_key_cmd_term_(htab, term_key_ctrl_right, &key_cmd_ctrl_arrow_right);
	add_key_cmd_term_(htab, term_key_alt_up, &key_cmd_alt_up);
	add_key_cmd_term_(htab, term_key_alt_down, &key_cmd_alt_down);

	add_key_cmd_term_(htab, term_key_backspace, &key_cmd_backspace);
	add_key_cmd_term_(htab, term_key_home, &key_cmd_home);
	add_key_cmd_term_(htab, term_key_end, &key_cmd_end);
	add_key_cmd_term_(htab, term_key_enter, &key_cmd_enter);
	add_key_cmd_term_(htab, term_key_tab, &key_cmd_tab);
}
