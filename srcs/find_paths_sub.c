/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:16:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 18:37:33 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path		*create_path_elem(void)
{
	t_path *path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);
	path->rooms = NULL;
	path->len = 0;
	path->ants_to_dispatch = 0;
	path->dispatched_ants = 0;
	path->next = NULL;
	return (path);
}

t_pathelem	*create_pathelem_elem(t_entree *curr, t_entree *prev)
{
	t_pathelem	*pathelem;

	if (!(pathelem = (t_pathelem*)malloc(sizeof(t_pathelem))))
		return (NULL);
	pathelem->curr = curr;
	pathelem->prev = prev;
	return (pathelem);
}

void		add_new_path_to_paths_list(t_global *gl, t_path *new_path)
{
	t_path *path;

	if (NULL == gl->paths)
		gl->paths = new_path;
	else
	{
		path = gl->paths;
		while (path->next)
			path = path->next;
		path->next = new_path;
	}
}

/*
**	We prevent the start and end room from being marked as visited, otherwise \
**	it would prevent the finding of other pathes.
*/

void		mark_new_path_rooms_as_visited(t_global *gl, t_path *new_path, \
										int *visited)
{
	t_room		*room;
	t_entree	*ent;

	room = new_path->rooms;
	while (room)
	{
		if (0 != ft_strcmp(gl->start, room->name)
				&& 0 != ft_strcmp(gl->end, room->name))
			if ((ent = dict_search(gl->dict, room->name)))
				visited[ENT_DATA->vertex_nb] = 1;
		room = room->next;
	}
}

/*
**	The variable maxNbAnts will contain the max value of ants that \
**	the already accepted paths can accept before accepting the new path.
*/

int			check_new_path_fastens_dispatch(t_global *gl, t_path *new_path)
{
	t_path	*path;
	int		max_nb_ants;

	if (NULL == gl->paths)
		return (1);
	path = gl->paths;
	max_nb_ants = 0;
	while (path)
	{
		max_nb_ants += new_path->len + 1 - path->len;
		path = path->next;
	}
	if (gl->nb_ants > max_nb_ants)
		return (1);
	free_paths(new_path);
	return (0);
}
