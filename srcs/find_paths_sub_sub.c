/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_sub_sub.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:47:06 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 19:57:30 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	free_non_empty_stack(t_stack *stack)
{
	void *content;

	while ((content = pop_stack(stack)) != NULL)
		free (content);
	free(stack);
}
