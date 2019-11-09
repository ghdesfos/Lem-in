/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:38:59 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/07 19:17:26 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_non_visited_neighbors(t_entree *ent, t_queue *queue, \
									int *new_visited)
{
	t_pathelem	*new_pathelem;
	int			i;

	i = -1;
	while (++i < ENT_DATA->nb_values)
	{
		if (new_visited[ENT_CH_DATA(i)->vertex_nb] == 0)
		{
			new_pathelem = create_pathelem_node((ENT_DATA->values)[i], ent);
			enqueue(queue, (void*)new_pathelem);
			new_visited[ENT_CH_DATA(i)->vertex_nb] = 1;
		}
	}
}

t_room	*add_room_elem_to_path(t_path *path, t_pathelem *pathelem)
{
	t_room *room;

	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->name = ft_strdup(((t_keyvalue*)(pathelem->curr->data))->key);
	room->x = ((t_keyvalue*)(pathelem->curr->data))->x;
	room->y = ((t_keyvalue*)(pathelem->curr->data))->y;
	room->next = path->rooms;
	path->rooms = room;
	path->len += 1;
	return (room);
}

t_path	*reconstitute_path(t_stack *stack, t_entree *start)
{
	t_path		*path;
	t_pathelem	*pathelem;
	t_entree	*prev;

	if (!(path = create_path_node()))
		return (NULL);
	pathelem = (t_pathelem*)pop_stack(stack);
	while (pathelem->curr != start)
	{
		if (NULL == add_room_elem_to_path(path, pathelem))
			return (NULL);
		prev = pathelem->prev;
		while (pathelem->curr != prev)
		{
			free(pathelem);
			pathelem = (t_pathelem*)pop_stack(stack);
		}
	}
	free(pathelem);
	free_non_empty_stack(stack);
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
	t_pathelem	*pathelem;
	int			new_visited[gl->nb_rooms];
	int			i;

	queue = init_queue();
	stack = init_stack();
	i = -1;
	while (++i < gl->nb_rooms)
		new_visited[i] = visited[i];
	enqueue(queue, (void*)create_pathelem_node(start, NULL));
	while (!is_empty_queue(queue))
	{
		pathelem = (t_pathelem*)dequeue(queue);
		push_stack(stack, pathelem);
		if (pathelem->curr == end)
			break ;
		add_non_visited_neighbors(pathelem->curr, queue, new_visited);
	}
	free_non_empty_queue(queue);
	if (pathelem->curr == end)
		return (reconstitute_path(stack, start));
	free_non_empty_stack(stack);
	return (NULL);
}

void	find_paths(t_global *gl)
{
	t_entree	*start;
	t_entree	*end;
	t_path		*new_path;
	int			visited[gl->nb_rooms];
	int			i;

	start = dict_search(gl->dict, gl->start);
	end = dict_search(gl->dict, gl->end);
	i = -1;
	while (++i < gl->nb_rooms)
		visited[i] = 0;
	while ((new_path = find_specific_path(gl, visited, start, end))
			&& check_new_path_fastens_dispatch(gl, new_path))
	{
		mark_new_path_rooms_as_visited(gl, new_path, visited);
		add_new_path_to_paths_list(gl, new_path);
	}
	find_paths_error_management(gl);
	if (FLAG_V & gl->options)
		apply_paths_to_visualizer_map(gl);
}
