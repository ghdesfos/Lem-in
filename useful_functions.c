/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:45:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/24 14:21:14 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char	*ft_strtrim_free(char *str)
{
	char *newStr;

	if (!str)
		return (NULL);
	newStr = ft_strtrim(str);
	free(str);
	return (str);
}
