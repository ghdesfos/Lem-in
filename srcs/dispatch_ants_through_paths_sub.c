/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_ants_through_paths_sub.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:24:04 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 17:14:00 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_dispatch	*create_dispatch_elem(int ant_nb, t_path *path)
{
	t_dispatch *dispatch;

	if (!(dispatch = (t_dispatch*)malloc(sizeof(t_dispatch))))
		return (NULL);
	dispatch->antNb = ant_nb;
	dispatch->room = path->rooms;
	dispatch->next = NULL;
	return (dispatch);
}

int			check_all_ants_have_reached_end(t_global *gl, int dispatched_ants, \
											t_dispatch **dis_tab)
{
	int all_paths_empty;
	int	i;

	all_paths_empty = 1;
	i = -1;
	while (++i < gl->nbPaths)
		if (disTab[i] != NULL)
			all_paths_empty = 0;
	if (all_paths_empty == 1 && dispatched_ants == gl->nbAnts)
		return (1);
	return (0);
}
