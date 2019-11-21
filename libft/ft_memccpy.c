/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:34:30 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 13:10:50 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c, \
					size_t n)
{
	char	*cdst;
	char	*csrc;
	size_t	i;

	cdst = (char*)dst;
	csrc = (char*)src;
	i = 0;
	while (i < n)
	{
		if (csrc[i] == (char)c)
		{
			cdst[i] = csrc[i];
			return ((void*)(cdst + i + 1));
		}
		cdst[i] = csrc[i];
		i++;
	}
	return (NULL);
}
