/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:42:04 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 13:04:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	if (!(new = ft_strdup(s)))
		return (NULL);
	i = -1;
	while (new[++i])
		new[i] = (*f)(new[i]);
	return (new);
}
