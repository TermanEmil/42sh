/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_formats.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:39:00 by eterman           #+#    #+#             */
/*   Updated: 2016/11/28 22:11:50 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FORMATS_H
# define T_FORMATS_H

typedef struct		s_formats
{
	char			flags[6];
	int				width;
	int				precision;
	int				precision_specified;
	char			length[3];
	char			specifier;
	char			*to_print;
	int				null_arg;
}					t_formats;

#endif
