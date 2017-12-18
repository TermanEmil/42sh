/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_named_types.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <terman.emil@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 18:34:45 by eterman           #+#    #+#             */
/*   Updated: 2017/05/29 20:01:03 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHORT_NAMED_TYPES_H
# define SHORT_NAMED_TYPES_H

/*
** So you can cast int to pointer
** https://stackoverflow.com/questions/8487380/
** how-to-cast-an-integer-to-void-pointer
*/

# define UINT_VOID(X) ((void*)(uintptr_t)X)

typedef unsigned long long	t_ull;
typedef unsigned long		t_ul;
typedef unsigned int		t_uint;
typedef uintmax_t			t_max;
typedef unsigned char		t_uchar;
typedef long long			t_ll;
typedef long double			t_ld;

#endif
