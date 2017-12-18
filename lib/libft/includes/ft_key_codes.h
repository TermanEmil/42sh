/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_codes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 11:57:36 by eterman           #+#    #+#             */
/*   Updated: 2017/06/22 18:35:27 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KEY_CODES_H
# define FT_KEY_CODES_H

typedef char const			*t_term_key[16];

/*
** Arrows
*/

# define FT_KEY_UP			"\033[A"
# define FT_KEY_DOWN		"\033[B"
# define FT_KEY_LEFT		"\033[D"
# define FT_KEY_RIGHT		"\033[C"
# define FT_KEY_CTRL_LEFT	"\033[1;5D"
# define FT_KEY_CTRL_RIGHT	"\033[1;5C"
# define FT_KEY_ALT_UP		"\033[1;3A"
# define FT_KEY_ALT_DOWN	"\033[1;3B"

# define FT_KEY_DEL			"\033[3~"
# define FT_KEY_BACKSPACE	"\x7f"
# define FT_KEY_CTRL_A		"\01"
# define FT_KEY_CTR_F		"\06"
# define FT_KEY_NL			"\n"
# define FT_KEY_CARRIAG_RET "\r"
# define FT_KEY_ALT_ENTER	"\033\012"
# define FT_KEY_ALT_DEL		"\033[3;3~"
# define FT_KEY_SHIFT_TAB	"\033[Z"
# define FT_KEY_SHIFT_DEL	"\033[3;2~"
# define FT_KEY_ESC			"\033"
# define FT_KEY_HOME1		"\033OH"
# define FT_KEY_HOME2		"\033[H"
# define FT_KEY_END1		"\033OF"
# define FT_KEY_END2		"\033[F"
# define FT_EOT				"\004"

# define FTI_KEY_UP			4283163
# define FTI_KEY_DOWN		4348699
# define FTI_KEY_LEFT		4479771
# define FTI_KEY_RIGHT		4414235
# define FTI_KEY_DEL		2117294875
# define FTI_KEY_BACKSPACE	127
# define FTI_KEY_CTRL_A		1
# define FTI_KEY_CTR_F		6
# define FTI_KEY_ALT_ENTER	2587
# define FTI_KEY_ALT_DEL	993221403
# define FTI_KEY_SHIFT_TAB	5921563
# define FTI_KEY_SHIFT_DEL	993221403
# define FTI_KEY_ESC		27
# define FTI_EOT			4

/*
** Used by termcap
** First, call term_make_termcap_keys_work()
** Then, foreach tab, key_code = tgetstr(tab[i]);
** Those keys starting with "term_" is a termcap key.
*/

// static const int a = 1;

static t_term_key const		term_key_up = {"ku", FT_KEY_UP};
static t_term_key const		term_key_down = {"kd", FT_KEY_DOWN};
static t_term_key const		term_key_left = {"kl", FT_KEY_LEFT};
static t_term_key const		term_key_right = {"kr", FT_KEY_RIGHT};
static t_term_key const		term_key_ctrl_left = {FT_KEY_CTRL_LEFT};
static t_term_key const		term_key_ctrl_right = {FT_KEY_CTRL_RIGHT};
static t_term_key const		term_key_alt_up = {FT_KEY_ALT_UP};
static t_term_key const		term_key_alt_down = {FT_KEY_ALT_DOWN};
static t_term_key const		term_key_enter = {FT_KEY_NL, FT_KEY_CARRIAG_RET};

static t_term_key const		term_key_next_pag = {"kN", "\xe[5~"};
static t_term_key const		term_key_prev_pag = {"kP", "\xe[6~"};
static t_term_key const		term_key_backspace = {"kb", FT_KEY_BACKSPACE};
static t_term_key const		term_key_del = {"kD", FT_KEY_DEL};
static t_term_key const		term_key_end = {"@7", FT_KEY_END1, FT_KEY_END2};
static t_term_key const		term_key_home =
								{"kh", "kH", FT_KEY_HOME1, FT_KEY_HOME2};

#endif
