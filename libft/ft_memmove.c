/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:35:48 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 13:09:56 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;
	size_t	i;

	if (dst == src || len == 0)
		return (dst);
	cdst = (char*)dst;
	csrc = (char*)src;
	i = 0;
	while (i < len)
	{
		if (cdst < csrc)
			cdst[i] = csrc[i];
		else
			cdst[len - i - 1] = csrc[len - i - 1];
		i++;
	}
	return (dst);
}
