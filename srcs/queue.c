/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 08:42:28 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 19:37:59 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

struct s_queue	*init_queue(void)
{
	t_queue *queue;

	if (!(queue = (t_queue*)malloc(sizeof(t_queue))))
		return (0);
	queue->first = 0;
	queue->last = 0;
	return (queue);
}

void			enqueue(struct s_queue *queue, void *content)
{
	t_node *new;

	if (!queue || !content)
		return ;
	if (!(new = (t_node*)malloc(sizeof(t_node))))
		return ;

	printf("QUEUE NODE %p\n", new);
	new->content = content;
	new->next = NULL;
	if (queue->first == 0)
	{
		queue->first = new;
		queue->last = new;
	}
	else
	{
		queue->last->next = new;
		queue->last = new;
	}
}

void			*dequeue(struct s_queue *queue)
{
	t_node	*tmp;
	void	*content;

	if (!queue)
		return (0);
	if (!(queue->first))
		return (0);
	tmp = queue->first;
	content = tmp->content;
	if (queue->first == queue->last)
	{
		queue->first = 0;
		queue->last = 0;
	}
	else
		queue->first = queue->first->next;
	free(tmp);
	return (content);
}

void			*peek_queue(struct s_queue *queue)
{
	if (!queue)
		return (0);
	if (!(queue->first))
		return (0);
	return (queue->first->content);
}

int				is_empty_queue(struct s_queue *queue)
{
	if (!queue)
		return (1);
	if (!(queue->first))
		return (1);
	return (0);
}
