/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_free_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:03:21 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/11 12:38:41 by ghdesfos         ###   ########.fr       */
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

void	free_dispatchs(t_dispatch **dispatchs, int size, int flag)
{
	int i;

	i = -1;
	while (++i < size)
		free(dispatchs[i]);
	if (flag)
		free(dispatchs);
}

void	free_non_empty_stack(t_stack *stack)
{
	void *content;

	while ((content = pop_stack(stack)) != NULL)
		free(content);
	free(stack);
}

void	free_non_empty_queue(t_queue *queue)
{
	void *content;

	while ((content = dequeue(queue)) != NULL)
		free(content);
	free(queue);
}
