/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:37:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 23:20:50 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t max)
{
	char	*new;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	if (max < len)
		len = max;
	new = NULL;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = str[i];
	new[len] = 0;
	return (new);
}
