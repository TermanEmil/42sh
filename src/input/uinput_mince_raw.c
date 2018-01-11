#include "shell42.h"
#include "shinput.h"

/*
** uinput == user input
*/

static inline t_bool		key_is_valid_to_be_added_to_buf(
								char const * const raw)
{
	if (get_displayed_alternative(raw, NULL) != NULL)
		return (TRUE);
	else if (ft_strlen(raw) > 1)
		return (char_is_utf8((unsigned char*)raw));
	else
		return (ft_isprint(raw[0]));
}

/*
** Inserts the given sequence in the shell data current input.
** First it inserts in the get_shdata()->input.current.input->keys list.
** Then I print the the given sequence, arranging the cursor.
** After that, I reprint everything, so I can be sure that everything works fine
*/

static inline void			uinput_insert_seq(t_shinput_seq seq)
{
	size_t				final_pos;

	if (seq.count <= 0)
		return;

	input_seq_insert_seq(g_current_in->input, g_current_in->cursor_pos, &seq);
	IF_TERM(term_cursor_off());

	final_pos = g_current_in->cursor_pos + seq.count;
	g_current_in->cursor_pos = final_pos - 1;

	IF_TERM(uinput_print_seq(seq.count));
	IF_TERM(input_reprint(g_current_in));

	g_current_in->cursor_pos = final_pos;

	IF_TERM(term_cursor_on());
}

/*
** Adds the first 'symbol' from the raw_in in seq. After that, moves the
** raw_in forward with the length of the found symbol (it may be 3 for 字).
*/

static inline void			process_raw_as_normal_input(
								char const ** raw_in,
								t_shinput_seq * const seq)
{
	char const	*utf8_char;
	char 		buf[5];

	utf8_char = utf8_get_first((unsigned char*)*raw_in);
	if (utf8_char == NULL)
		ft_strncpy_terminate(buf, *raw_in, 1);
	else
		ft_strcpy(buf, utf8_char);

	*raw_in += ft_strlen(buf);

	if (!key_is_valid_to_be_added_to_buf(buf))
		return;

	input_seq_add_key(seq, sh_inkey_get_from_raw(buf));
}

/*
** Mince = фарш
** If in raw_in are some key_cmds, like tab or enter, they will be processed.
*/

t_shinput_seq	uinput_mince_raw(char const *raw_in)
{
	t_shinput_seq		seq;
	t_hashpair const	*cmd_hpair;

	seq = shinput_seq_construct();
	while (*raw_in && !g_shinput->signaled_sigint)
	{		
		cmd_hpair = shell_get_key_cmd(raw_in);
		if (cmd_hpair != NULL)
		{
			if (seq.count > 0)
			{
				uinput_insert_seq(seq);
				seq.keys = NULL;
				seq.count = 0;
			}
			CAST(cmd_hpair->val.mem, t_key_cmd_f*)();
			raw_in += ft_strlen(cmd_hpair->key.mem);
		}
		else
			process_raw_as_normal_input(&raw_in, &seq);
	}
	if (seq.count > 0)
		uinput_insert_seq(seq);
	// if (g_shdata.subshell_cmd)
	// 	ft_printf("helllozo\n");
	return (seq);
}
