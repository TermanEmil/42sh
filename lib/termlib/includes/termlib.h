#ifndef TERMLIB_H
# define TERMLIB_H

# include <termcap.h>
# include <termios.h>
# include "libft.h"
# include "ft_errors.h"
# include <stdio.h>
# include <sys/ioctl.h>

/*
** References:
** ICANON, VMIN, VTIME, TCSAFLUSH
** https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_chapter/libc_17.html
*/

/*
** FD_WR == where it will write
*/

# define FD_WR STDERR_FILENO

typedef struct termios	t_termios;

/*
** term_buf must not be changed during the entire use of tgetent, it's just a
** storage.
** tmp_buf is a storage used for different terminal interogations, like tgetstr.
*/

typedef struct		s_term_data
{
	t_termios		old_term;
	char			term_buf[2048];
	char			tmp_buf[2048];
}					t_term_data;

/*
** General use
*/

char				*term_getch(void);
void				term_blink(void);
int					term_get_current_tty(void);
int					term_get_cursor_pos(int tty, int *row, int *col);
void				term_del_char(void);
int					term_printf(int x, int y, char const *format, ...);
void				term_putnewl(void);

/*
** Cursor
*/

void				term_cursor_on(void);
void				term_cursor_off(void);
void				term_cursor_goto(int x, int y);
void				term_cursor_goto_home(void);
void				term_move_cursor_to_left_most(void);
void				term_save_cursor_pos(void);
void				term_restore_cursor_pos(void);

/*
** Scroll
*/

void				term_scroll_up(void);
void				term_scroll_down(void);

/*
** Clear
*/

void				term_clear_screen(void);
void				term_clear_n_chars(size_t n);
void				term_clear_from_cursor_to_end_line(void);
void				term_clear_from_cursor_to_bot(void);

/*
** Random cursor mode
*/

void				term_random_cursor_mode_on(void);
void				term_random_cursor_mode_off(void);

/*
** Input insert mode
*/

void				term_enter_input_insert_mode(void);
void				term_leave_input_insert_mode(void);

/*
** Window sizes
*/

ssize_t				term_get_width(void);
ssize_t				term_get_height(void);

/*
** General initialisers / restorees
*/

void				term_init_internal_data(char const *termtype,
						char *term_buf);
void				term_setup(char const *termtype, t_term_data *term_data);
void				term_restore(t_termios const *old_term);
void				term_save_current_term_data(void);
void				term_restore_to_old_term_data(void);
void				term_full_reset(void);
void				term_make_termcap_keys_work(void);

/*
** Getters Setters
*/

t_term_data			*term_get_data(void);
t_termios			term_get_current_term_data(void);
void				term_set_current_term_data(t_termios const *term_to_set);

/*
** Canonical form
*/

void				term_enable_canonical_form_write(t_termios *term);
void				term_enable_canonical_form(void);
void				term_restore_canonical_form_write(t_termios *term,
						t_termios const *old_term);
void				term_restore_canonical_form(void);

/*
** Echo
*/

void				term_echo_off_write(t_termios *term);
void				term_echo_off(void);
void				term_echo_restore_write(t_termios *term,
						t_termios const *old_term);
void				term_echo_restore(void);

/*
** Character printing modes
*/

void				term_start_half_bright_mode(void);
void				term_start_dark_mode(void);
void				term_start_reverse_mode(void);
void				term_end_standout_mode(void);
void				term_start_underlining(void);
void				term_end_underlining(void);

/*
** Private
*/

int					term_tputs_putchar(int c);
void				term_tputs(char const *attr_name, size_t nlines, char *buf);
void				term_try_tputs(char const *attr_name, size_t nlines,
						char *buf);
void				term_tgoto_call(char const *attr, size_t nlines,
						int x, int y);
char const			*term_tgetstr(char const *attr);

#endif