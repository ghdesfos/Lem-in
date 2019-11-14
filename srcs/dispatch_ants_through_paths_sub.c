/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_ants_through_paths_sub.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:24:04 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:13:08 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_dispatch	*create_dispatch_elem(int ant_nb, t_path *path, int *coor, \
									int delay)
{
	t_dispatch *dispatch;

	if (!(dispatch = (t_dispatch*)malloc(sizeof(t_dispatch))))
		return (NULL);
	dispatch->ant_nb = ant_nb;
	dispatch->room = path->rooms;
	if (coor)
	{
		dispatch->coor[0] = coor[0];
		dispatch->coor[1] = coor[1];
	}
	dispatch->delay = delay;
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
	while (++i < gl->nb_paths)
		if (dis_tab[i] != NULL)
			all_paths_empty = 0;
	if (all_paths_empty == 1 && dispatched_ants == gl->nb_ants)
		return (1);
	return (0);
}
