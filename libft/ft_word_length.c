/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:23:22 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/06 23:20:02 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_length(char *str, char *sep)
{
	size_t len;

	if (!str || *str == 0)
		return (0);
	if (!sep || *sep == 0)
		return (ft_strlen(str));
	len = 0;
	while (str[len] && !ft_strchr(sep, str[len]))
		len++;
	return (len);
}
