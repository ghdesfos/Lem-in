/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_free_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:03:21 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/25 09:06:21 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_words(char **words)
{
	int n;

	if (!words)
		return ;
	n = -1;
	while (words[++n])
		free(words[n]);
	free(words);
}
