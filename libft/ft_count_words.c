/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:21:07 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 23:07:24 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*move_to_char_after_end_of_word(char *str, char *sep)
{
	while (*str && !ft_strchr(sep, *str))
		str++;
	return (str);
}

static char		*move_to_next_word(char *str, char *sep)
{
	while (ft_strchr(sep, *str))
		str++;
	return (str);
}

size_t			ft_count_words(char *str, char *sep)
{
	size_t count;

	count = 0;
	if (!str || *str == 0)
		return (0);
	if (!sep || *sep == 0)
		return (1);
	while (*str)
	{
		str = move_to_next_word(str, sep);
		if (*str != 0)
			count++;
		str = move_to_char_after_end_of_word(str, sep);
	}
	return (count);
}
