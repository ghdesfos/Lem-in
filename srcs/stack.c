/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 08:48:21 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 19:38:27 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

struct s_stack	*init_stack(void)
{
	struct s_stack *stack;

	if (!(stack = (struct s_stack*)malloc(sizeof(struct s_stack))))
		return (NULL);
	stack->top = NULL;
	return (stack);
}

void			*pop_stack(struct s_stack *stack)
{
	struct s_node	*node;
	void			*content;

	if (!stack || (!stack->top))
		return (NULL);
	node = stack->top;
	content = node->content;
	stack->top = stack->top->next;
	free(node);
	return (content);
}

void			push_stack(struct s_stack *stack, void *content)
{
	struct s_node *new;

	if (!stack || !content)
		return ;
	if (!(new = (struct s_node*)malloc(sizeof(struct s_node))))
		return ;

	printf("STACK NODE %p\n", new);
	new->content = content;
	new->next = stack->top;
	stack->top = new;
}

void			*peek_stack(struct s_stack *stack)
{
	if (!stack || !(stack->top))
		return (NULL);
	return (stack->top->content);
}

int				is_empty_stack(struct s_stack *stack)
{
	if (!stack || !(stack->top))
		return (1);
	return (0);
}
