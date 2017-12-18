/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eterman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 12:07:24 by eterman           #+#    #+#             */
/*   Updated: 2016/10/22 12:09:32 by eterman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define IF_IS_NULL(x) if (!x) return (NULL)

/*
** Counts the number of words.
** Changes separators to null-byte for strdup
*/

static unsigned int	count_clean_words(char *s, char sep)
{
	unsigned int	result;

	result = 0;
	while (*s)
	{
		while (*s == sep)
		{
			*s = '\0';
			s++;
		}
		if (*s != sep && *s != '\0')
		{
			while (*s && *s != sep)
				s++;
			result++;
		}
	}
	return (result);
}

/*
** Changes the pointer to the beggining of the
** next word
*/

static void			point_to_next_word(char **s)
{
	while (**s)
		*s += 1;
	while (**s == '\0')
		*s += 1;
}

char				**ft_strsplit(char const *s, char sep)
{
	char			**result;
	char			*mem_s;
	unsigned int	nr_words;
	unsigned int	i;

	IF_IS_NULL(s);
	mem_s = ft_strdup(s);
	IF_IS_NULL(mem_s);
	nr_words = count_clean_words(mem_s, sep);
	if (nr_words == 0)
	{
		result = (char**)malloc(1);
		*result = NULL;
		return (result);
	}
	result = (char**)malloc(sizeof(char*) * nr_words + 1);
	if ((i = 0) || *mem_s == '\0')
		point_to_next_word(&mem_s);
	while (i < nr_words)
	{
		result[i++] = ft_strdup(mem_s);
		(i < nr_words) ? (point_to_next_word(&mem_s)) : (1);
	}
	result[i] = 0;
	return (result);
}
