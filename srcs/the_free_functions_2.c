/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_free_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:03:21 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 17:53:15 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	free_lines(t_line *lines)
{
	t_line *tmp;
	t_line *next;

	if (!lines)
		return ;
	tmp = lines;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->line);
		free(tmp);
		tmp = next;
	}
}
