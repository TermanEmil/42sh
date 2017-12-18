/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 11:41:34 by eterman           #+#    #+#             */
/*   Updated: 2017/02/19 14:15:57 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H

/*
** Text color
*/

# define C_EOC				"\033[0m"

# define C_RED				"\033[31m"
# define C_GREEN			"\033[32m"
# define C_YELLOW			"\033[33m"
# define C_BLUE				"\033[34m"
# define C_MAGENTA			"\033[35m"
# define C_CYAN				"\033[36m"
# define C_GRAY				"\033[90m"

# define C_BLACK			"\033[30m"
# define C_WHITE			"\033[97m"

# define C_LRED				"\033[91m"
# define C_LGREEN			"\033[92m"
# define C_LYELLOW			"\033[93m"
# define C_LBLUE			"\033[94m"
# define C_LMAGENTA			"\033[95m"
# define C_LCYAN			"\033[96m"
# define C_LGRAY			"\033[37m"

/*
** Background color
*/

# define BG_RESET			"\033[49m"

# define BG_LRED			"\033[41m"
# define BG_LGREEN			"\033[42m"
# define BG_LYELLOW			"\033[43m"
# define BG_LBLUE			"\033[44m"
# define BG_LMAGENTA		"\033[45m"
# define BG_LCYAN			"\033[46m"
# define BG_LGRAY			"\033[47m"

# define BG_BLACK			"\033[40m"
# define BG_WHITE			"\033[107m"

# define BG_RED				"\033[101m"
# define BG_GREEN			"\033[102m"
# define BG_YELLOW			"\033[103m"
# define BG_BLUE			"\033[104m"
# define BG_MAGENTA			"\033[105m"
# define BG_CYAN			"\033[106m"
# define BG_GRAY			"\033[100m"

/*
** Files
*/

# define C_DIR				"\033[01;34m"
# define C_PIPE				"\033[33m"
# define C_BLOCK			"\033[01;33m"
# define C_LINK				"\033[01;36m"
# define C_SOCKET			"\033[01;35m"
# define C_EXEC				"\033[01;32m"
# define C_CHRDEV			"\033[01;33m"
# define C_ORPHAN			"\033[40;31m"
# define C_DENIED			C_GRAY
# define C_ARCHIVE			C_RED
# define C_CODE				C_LGRAY
# define C_DISPLAY			"\033[01;35m"

#endif
