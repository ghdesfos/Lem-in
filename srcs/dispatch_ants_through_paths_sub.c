/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_ants_through_paths_sub.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:24:04 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 17:24:10 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_dispatch	*create_dispatch_elem(int antNb, t_path *path)
{
	t_dispatch *dispatch;

	if (!(dispatch = (t_dispatch*)malloc(sizeof(t_dispatch))))
		return (NULL);
	dispatch->antNb = antNb;
	dispatch->room = path->rooms;
	dispatch->next = NULL;
	return (dispatch);
}

int		check_all_ants_have_reached_end(t_global *gl, int dispatchedAnts, \
											t_dispatch **disTab)
{
	int allPathsEmpty;
	int	i;

	allPathsEmpty = 1;
	i = -1;
	while (++i < gl->nbPaths)
		if (disTab[i] != NULL)
			allPathsEmpty = 0;
	if (allPathsEmpty == 1 && dispatchedAnts == gl->nbAnts)
		return (1);
	return (0);
}
