/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:31:01 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/07 19:09:41 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	val;

	while (*str == ' ' || *str == '\n' || *str == '\t' \
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	val = 0;
	while (*str >= '0' && *str <= '9')
	{
		val = 10 * val + *str - '0';
		if (sign == -1 && val > (size_t)9223372036854775807)
			return (0);
		if (sign == 1 && val > (size_t)9223372036854775807)
			return (-1);
		str++;
	}
	return ((int)(sign * val));
}
