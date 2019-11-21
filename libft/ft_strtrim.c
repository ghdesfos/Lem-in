/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:45:11 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 13:06:40 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	if (*s == 0)
		return (ft_strdup(""));
	len = 0;
	while (s[len])
	{
		while (s[len] && s[len] != ' ' \
				&& s[len] != '\n' && s[len] != '\t')
			len++;
		i = 0;
		while (s[len + i] == ' ' || s[len + i] == '\n' || s[len + i] == '\t')
			i++;
		if (s[len + i] == 0)
			break ;
		len += i;
	}
	return (ft_strsub(s, 0, len));
}
