/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:38:59 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 20:05:13 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	add_non_visited_neighbors(t_entree *ent, t_queue *queue, \
									int *newVisited)
{
	t_pathelem	*newPathElem;
	int			i;

	i = -1;
	while (++i < ENT_DATA->nbValues)
	{
		if (newVisited[ENT_CH_DATA(i)->vertexNb] == 0)
		{
			newPathElem = create_pathelem_elem((ENT_DATA->values)[i], ent);
			enqueue(queue, (void*)newPathElem);
			newVisited[ENT_CH_DATA(i)->vertexNb] = 1;
		}
	}
}

t_room	*add_room_elem_to_path(t_path *path, t_pathelem *pathElem)
{
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->name = ((t_keyvalue*)(pathElem->curr->data))->key;
	room->name = ((t_keyvalue*)(pathElem->curr->data))->key;
	room->name = ((t_keyvalue*)(pathElem->curr->data))->key;
	room->next = path->rooms;
	path->rooms = room;
	path->len += 1;
	return (room);
}

t_path	*reconstitute_path(t_stack *stack, t_entree *start)
{
	t_path		*path;
	t_pathelem	*pathElem;
	t_entree	*prev;

	if (!(path = create_path_elem()))
		return (NULL);
	pathElem = (t_pathelem*)pop_stack(stack);
	while (pathElem->curr != start)
	{
		if (NULL == add_room_elem_to_path(path, pathElem))
			return (NULL);
		prev = pathElem->prev;
		while (pathElem->curr != prev)
		{
			free(pathElem);
			pathElem = (t_pathelem*)pop_stack(stack);
		}
	}
	free(pathElem);
	free(stack);
	return (path);
}

/*
**	We explore all possible paths, never visiting a node already visited.
*/

t_path	*find_specific_path(t_global *gl, int *visited, t_entree *start, \
							t_entree *end)
{
	t_queue		*queue;
	t_stack		*stack;
	t_pathelem	*pathElem;
	int			newVisited[gl->nbRooms];
	int			i;
	
	queue = init_queue();
	stack = init_stack();
	i = -1;
	while (++i < gl->nbRooms)
		newVisited[i] = visited[i];
	enqueue(queue, (void*)create_pathelem_elem(start, NULL));
	while (!is_empty_queue(queue))
	{

		printf("PATHELEM %p\n", pathElem);
		pathElem = (t_pathelem*)dequeue(queue);
		push_stack(stack, pathElem);
		if (pathElem->curr == end)
			break ;
		add_non_visited_neighbors(pathElem->curr, queue, newVisited);
	}
	free(queue);
	if (pathElem->curr == end)
		return (reconstitute_path(stack, start));
//	free_non_empty_stack(stack);
	return (NULL);
}

void	find_paths(t_global *gl)
{
	t_entree	*start;
	t_entree	*end;
	t_path		*newPath;
	int			visited[gl->nbRooms];
	int			i;

	start = dict_search(gl->dict, gl->start);
	end = dict_search(gl->dict, gl->end);
	i = -1;
	while (++i < gl->nbRooms)
		visited[i] = 0;
	while ((newPath = find_specific_path(gl, visited, start, end))
			&& check_new_path_fastens_dispatch(gl, newPath))
	{
		mark_new_path_rooms_as_visited(gl, newPath, visited);
		newPath->next = gl->paths;
		gl->paths = newPath;
		gl->nbPaths += 1;
		if (0 == gl->minPathLen || newPath->len < gl->minPathLen)
			gl->minPathLen = newPath->len;
		if (newPath->len > gl->maxPathLen)
			gl->maxPathLen = newPath->len;
	}
	find_paths_error_management(gl);
}
