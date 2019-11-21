/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:44:22 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 12:45:24 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*move_to_char_after_end_of_word(char *str, char c)
{
	while (*str && *str != c)
		str++;
	return (str);
}

static char		*move_to_next_word(char *str, char c)
{
	while (*str == c)
		str++;
	return (str);
}

static size_t	count_words(char *str, char c)
{
	size_t count;

	count = 0;
	while (*str)
	{
		str = move_to_next_word(str, c);
		if (*str != 0)
			count++;
		str = move_to_char_after_end_of_word(str, c);
	}
	return (count);
}

static size_t	word_length(char *str, char c)
{
	size_t len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	words_nb;
	size_t	word_len;
	size_t	i;
	size_t	j;

	if ((i = 0) == 0 && !s)
		return (NULL);
	words_nb = count_words((char*)s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (words_nb + 1))))
		return (NULL);
	tab[words_nb] = NULL;
	while (i < words_nb)
	{
		s = move_to_next_word((char*)s, c);
		word_len = word_length((char*)s, c);
		if (!(tab[i] = (char*)malloc(sizeof(char) * (word_len + 1))))
			return (NULL);
		j = -1;
		while (++j < word_len)
			tab[i][j] = s[j];
		tab[i++][word_len] = 0;
		s = move_to_char_after_end_of_word((char*)s, c);
	}
	return (tab);
}
