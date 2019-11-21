/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:42:12 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 13:07:46 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		new[i] = (*f)((unsigned int)i, s[i]);
	return (new);
}
