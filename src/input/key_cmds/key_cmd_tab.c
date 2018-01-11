#include "shell42.h"
#include "regex_tools.h"
#include <sys/types.h>
#include <dirent.h>

t_str	get_first_word_(t_lst_inkey **first_word_key)
{
	t_str			result;
	t_lst_inkey		*current_key;
	t_lst_inkey		*last_word_keys;
	t_rostr			key_meaning;

	current_key =
		ft_lstget(g_current_in->input->keys, g_current_in->cursor_pos - 1);

	last_word_keys = NULL;
	*first_word_key = NULL;
	for (; current_key; LTOPREV(current_key))
	{
		key_meaning = sh_inkey_get_meaning(LCONT(current_key, t_sh_inkey*));
		if (ft_strstr(" \t()[]{}\"\'\\$;|/", key_meaning))
			break;
		else
			ft_lst_push_front(&last_word_keys,
				ft_lstnew_nocpy(current_key->content, sizeof(void*)));
		*first_word_key = current_key;
	}
	result = word_to_str(last_word_keys);
	ft_lstdel(&last_word_keys, NULL);
	return result;
}

t_bool	word_is_cmd_(const t_lst_inkey *first_word_key)
{
	t_rostr		key_meaning;
	t_bool		was_space;
;
	was_space = FALSE;
	for (; first_word_key; LTOPREV(first_word_key))
	{
		key_meaning = sh_inkey_get_meaning(LCONT(first_word_key, t_sh_inkey*));
		if (ft_strstr("./", key_meaning))
			return FALSE;
		if (ft_strstr("();|", key_meaning))
			return TRUE;
		else if (was_space)
			return FALSE;
		if (ft_strequ(key_meaning, " "))
			was_space = TRUE;
	}
	if (g_shinput->history.current_in_index == -1)
		return TRUE;
	else
		return FALSE;
}

t_lst_str	*get_matches_from_path_(t_rostr path, t_rostr patern)
{
	DIR				*dir_path;
	struct dirent	*dir_buf;
	t_lst_str		*matches;

	matches = NULL;
	if ((dir_path = opendir(path)) == NULL)
	{
		errno = 0;
		return NULL;
	}
	while ((dir_buf = readdir(dir_path)) != NULL)
	{
		if (regex_mini_match(patern, dir_buf->d_name))
			ft_lstadd(&matches, ft_lstnew_str(dir_buf->d_name));
	}
	errno = 0;
	closedir(dir_path);
	return matches;
}

t_lst_str	*get_cmd_completion_(t_rostr first_word)
{
	t_rostr		path_val;
	t_str		*paths;
	t_lst_str	*matches;
	t_str		patern;
	int			i;
	
	path_val = htab_get_strval(g_shdata.shvars.env, new_hashmem_str("PATH"));
	if (path_val == NULL)
		return NULL;

	if ((paths = ft_strsplit(path_val, ':')) == NULL)
		ft_err_mem(TRUE);

	patern = ft_strmegajoin(2, "^", first_word);
	matches = NULL;
	for (i = 0; paths[i]; i++)
		ft_lstadd(&matches, get_matches_from_path_(paths[i], patern));
	free(patern);
	ft_free_bidimens(paths);
	return matches;
}

t_str		get_relative_path_(t_lst_inkey *first_word_key)
{
	t_str		result;
	t_rostr		key_meaning;
	t_lst_inkey	*relative_path_keys;

	relative_path_keys = NULL;
	LTOPREV(first_word_key);
	for (; first_word_key; LTOPREV(first_word_key))
	{
		key_meaning = sh_inkey_get_meaning(LCONT(first_word_key, t_sh_inkey*));
		if (ft_strstr(" ", key_meaning))
			break;
		ft_lst_push_front(&relative_path_keys,
			ft_lstnew_nocpy(first_word_key->content, sizeof(void*)));
	}
	if (ft_lstlen(relative_path_keys) == 0)
		result = ft_strdup("./");
	else
		result = word_to_str(relative_path_keys);
	ft_lstdel(&relative_path_keys, NULL);
	return result;
}

t_lst_str	*get_path_completion_(
				t_lst_inkey *first_word_key,
				t_rostr first_word)
{
	t_lst_str	*matches;
	t_str		path;
	t_str		patern;


	path = get_relative_path_(first_word_key);
	patern = ft_strmegajoin(2, "^", first_word);
	matches = get_matches_from_path_(path, patern);
	free(path);
	free(patern);
	return matches;
}

void	process_single_match_(t_rostr first_word, t_rostr match)
{
	t_shinput_seq	seq;

	if (ft_strlen(match + ft_strlen(first_word)) == 0)
		return;
	seq.keys = get_sh_inkeys_from_str(match + ft_strlen(first_word));
	seq.count = ft_lstlen(seq.keys);
	input_seq_insert_seq(g_current_in->input, g_current_in->cursor_pos, &seq);
	g_current_in->cursor_pos += seq.count;
	input_reprint_here(g_current_in);
}

void	process_multiple_matches_(const t_lst_str *matches)
{
	int	len;

	len = ft_lstlen(matches);
	term_putnewl();
	if (len > 20)
	{
		ft_printf("Print all %d matches? (y/n)", len);
		if (!ft_strequ(term_getch(), "y"))
		{
			term_putnewl();
			input_reprint_here(g_current_in);
			return;
		}
	}
	for (; matches; LTONEXT(matches))
	{
		ft_putstr(LCONT(matches, t_str));
		term_putnewl();
	}
	input_reprint_here(g_current_in);
}

int		key_cmd_tab()
{
	static t_bool	pressed_once;
	t_str			first_word;
	t_lst_inkey		*first_word_key;
	t_lst_str		*matches;

	first_word = get_first_word_(&first_word_key);
	if (first_word_key == NULL)
	{
		free(first_word);
		return 0;
	}
	if (word_is_cmd_(first_word_key))
		matches = get_cmd_completion_(first_word);
	else
		matches = get_path_completion_(first_word_key, first_word);

	if (ft_lstlen(matches) == 1)
	{
		process_single_match_(first_word, LCONT(matches, t_str));
		pressed_once = FALSE;
	}
	else if (ft_lstlen(matches) >= 1)
	{
		if (pressed_once)
		{
			process_multiple_matches_(matches);
			pressed_once = FALSE;
		}
		else
			pressed_once = TRUE;
	}

	ft_lstdel(&matches, &std_mem_del);
	free(first_word);
	return 0;
}