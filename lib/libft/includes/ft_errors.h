/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 09:36:07 by eterman           #+#    #+#             */
/*   Updated: 2017/02/20 18:22:47 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRORS_H
# define FT_ERRORS_H

# define ERR_EXIT_PROG 1
# define ERR_DONT_EXIT_PROG 0
# define PROJ_NAME (ft_err_get_proj_name(NULL))

extern char const	*g_proj_name;

void		ft_err_init_proj_name(char const *proj_name);
void		ft_err(const char *msg);
void		ft_fatal(const char *format, ...);
void		ft_err_mem(int exit_program);
int			ft_proj_err(const char *msg, int exit_program);
void		ft_error(int const exit_program, char const *format, ...);

#endif
