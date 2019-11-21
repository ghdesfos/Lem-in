/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:39:19 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 13:03:05 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = -1;
	while (++i < src_len)
		dst[i] = src[i];
	dst[src_len] = 0;
	return (dst);
}
