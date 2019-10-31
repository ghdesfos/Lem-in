/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:16:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 19:47:36 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

t_path		*create_path_elem(void)
{
	t_path *path;

	if (!(path = (t_path*)malloc(sizeof(t_path))))
		return (NULL);

	printf("POINTER CREATE PATH %p\n", path);
	path->rooms = NULL;
	path->len = 0;
	path->antsToDispatch = 0;
	path->dispatchedAnts = 0;
	path->next = NULL;
	return (path);
}

t_pathelem	*create_pathelem_elem(t_entree *curr, t_entree *prev)
{
	t_pathelem	*pathElem;

	if (!(pathElem = (t_pathelem*)malloc(sizeof(t_pathelem))))
		return (NULL);
	pathElem->curr = curr;

	printf("POINTER CREATE PATHELEM %p %s\n", pathElem, 
								((t_keyvalue*)(pathElem->curr->data))->key);
	pathElem->prev = prev;
	return (pathElem);
}

void	find_paths_error_management(t_global *gl)
{
	if (NULL == gl->paths)
	{
		ft_putstr_fd("ERROR\nthere is no path linking the start and end rooms\n", 2);
		free_global(gl);
		exit(-6);
	}
}

/*
**	We prevent the start and end room from being marked as visited, otherwise \
**	it would prevent the finding of other pathes.
*/

void	mark_new_path_rooms_as_visited(t_global *gl, t_path *newPath, \
										int *visited)
{
	t_room		*room;
	t_entree	*ent;

	room = newPath->rooms;
	while (room)
	{
		if (0 != ft_strcmp(gl->start, room->name)
				&& 0 != ft_strcmp(gl->end, room->name))
			if ((ent = dict_search(gl->dict, room->name)))
				visited[ENT_DATA->vertexNb] = 1;
		room = room->next;
	}

}

/*
**	The variable maxNbAnts will contain the max value of ants that \
**	the already accepted paths can accept before accepting the new path.
*/

int		check_new_path_fastens_dispatch(t_global *gl, t_path *newPath)
{
	t_path	*path;
	int		maxNbAnts;

	if (NULL == gl->paths)
		return (1);
	path = gl->paths;
	maxNbAnts = 0;
	while (path)
	{
		maxNbAnts += newPath->len + 1 - path->len;
		path = path->next;
	}
	if (gl->nbAnts > maxNbAnts)
		return (1);
	free_paths(newPath);
	return (0);
}
