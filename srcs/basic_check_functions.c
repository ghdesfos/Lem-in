/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_check_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:11:20 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/26 13:01:30 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// est ce bien un int? pas d'autres caracteres?
// est ce que le int n'est pas negatif?
// retour de la fonction --> -1 en cas d'erreur? comment choper et traiter \
// cela dans la fonction principale

int		check_contains_just_digits(char *line)
{
	if (!line)
		return (-1);
	while (*line)
	{
		if (*line < '0' || *line > '9')
			return (0);
		line++;
	}
	return (1);
}

int		check_is_a_positive_int(char *line)
{
	long val;

	if (!line)
		return (-1);
	if (!check_contains_just_digits(line))
		return (-1);
	val = 0;
	while (*line)
	{
		val = val * 10 + (*line - '0');
		if (val > INT_MAX)
			return (-1);
		line++;
	}
	return (val);
}
