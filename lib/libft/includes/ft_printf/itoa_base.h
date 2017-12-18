/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:38:58 by eterman           #+#    #+#             */
/*   Updated: 2016/11/30 11:11:18 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITOA_BASE_H
# define ITOA_BASE_H

# define VAL(X)				(variant->val.X)
# define LESS_THAN_BASE(X)	*less_than_base = ((t_max)VAL(X) < (t_max)base)
# define SET_INDEX(X)		*i = VAL(X) % base
# define DIV_VAL(X)			VAL(X) /= base

typedef union		u_multiple_type
{
	unsigned		u_val;
	t_ull			ull_val;
	t_ul			ul_val;
	unsigned short	h_val;
	unsigned char	uc_val;
	size_t			st_val;
	uintmax_t		max_val;
}					t_multiple_type;

typedef enum		e_type
{
	u_integer,
	u_long_int,
	u_long_long_int,
	u_short_int,
	u_char_val,
	size_t_val,
	max_val
}					t_type;

typedef struct		s_variant
{
	t_type			type;
	t_multiple_type	val;
	int				is_negative;
}					t_variant;

char				*va_arg_itoa(va_list *ap, int bs, int up, t_formats *frmts);
int					is_long(t_formats *formats);
void				negative_process(
						t_variant *variant,
						t_formats *formats,
						int base,
						long long *nb);
void				set_variant_value(
						t_variant *variant,
						t_formats *formats,
						va_list *ap,
						int base);
void				var_inf(
						int *i,
						int *less_than_base,
						int base,
						t_variant *variant);

#endif
