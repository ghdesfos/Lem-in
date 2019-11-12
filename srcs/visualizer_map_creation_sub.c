/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_map_creation_sub.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:25:55 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/11 21:45:29 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_rooms_to_visualizer_map(t_global *gl)
{
	t_map_elem	**map;
	t_room		*room;

	map = gl->map;
	room = gl->rooms;
	while (room)
	{
		if (0 == ft_strcmp(room->name, gl->start))
			map[room->x][room->y].pchar = CHAR_SOURCE;
		else if (0 == ft_strcmp(room->name, gl->end))
			map[room->x][room->y].pchar = CHAR_SINK;
		else
			map[room->x][room->y].pchar = CHAR_ROOM;
		room = room->next;
	}
}

/*
**	We want to draw the path starting from the leftest room, and then \
**	draw first horizontally and then vertically the path.
**	Hence we invert the coordinates if we're not in the case we want.
**	--> same comment, as for the functions:
**	- move_ants_to_next_room_in_visualizer()
**	- apply_specific_path_to_visualizer_map()
*/

#define CXY			map[x][y].pchar
#define NOT_A_ROOM	CXY != CHAR_ROOM && CXY != CHAR_SOURCE && CXY != CHAR_SINK

void	add_link_elements_to_visualizer_map(t_global *gl, \
											int *coor1, int *coor2)
{
	t_map_elem	**map;
	int			x;
	int			y;

	map = gl->map;
	(coor1[1] > coor2[1]) ? swap_coordinates(coor1, coor2) : NULL;
	x = coor1[0];
	y = coor1[1];
	while (y != coor2[1])
	{
		(coor1[1] < coor2[1]) ? y++ : y--;
		if (map[x][y].pchar == ' ')
			map[x][y].pchar = CHAR_HORIZ;
		else if (map[x][y].pchar == CHAR_VERTI)
			map[x][y].pchar = CHAR_INTERSECT;
	}
	(coor1[0] != coor2[0] && NOT_A_ROOM) ? map[x][y].pchar = CHAR_INTERSECT : 0;
	while (x != coor2[0])
	{
		(coor1[0] < coor2[0]) ? x++ : x--;
		if (map[x][y].pchar == ' ')
			map[x][y].pchar = CHAR_VERTI;
		else if (map[x][y].pchar == CHAR_HORIZ)
			map[x][y].pchar = CHAR_INTERSECT;
	}
}

void	add_link_to_visualizer_map(t_global *gl, char **words)
{
	t_entree	*ent1;
	t_entree	*ent2;
	int			coor1[2];
	int			coor2[2];

	if (!(ent1 = dict_search(gl->dict, words[0]))
			|| !(ent2 = dict_search(gl->dict, words[1])))
		return ;
	coor1[0] = ((t_keyvalue*)(ent1->data))->x;
	coor1[1] = ((t_keyvalue*)(ent1->data))->y;
	coor2[0] = ((t_keyvalue*)(ent2->data))->x;
	coor2[1] = ((t_keyvalue*)(ent2->data))->y;
	add_link_elements_to_visualizer_map(gl, coor1, coor2);
}

/*
**	We want to draw the path starting from the leftest room, and then \
**	draw first horizontally and then vertically the path.
**	Hence we invert the coordinates if we're not in the case we want.
**	--> same comment, as for the functions:
**	- add_link_elements_to_visualizer_map()
**	- move_ants_to_next_room_in_visualizer()
**
**	Hence the ifs conditions below.
*/

void	apply_specific_path_to_visualizer_map(t_global *gl, t_room *room)
{
	t_map_elem	**map;
	t_room		*next_room;
	int			x;
	int			y;

	map = gl->map;
	while (room->next)
	{
		next_room = room->next;
		x = room->x;
		y = room->y;
		if (room->y < next_room->y)
			while (y != next_room->y && (map[x][y].flag_path = 1) == 1)
				(room->y < next_room->y) ? y++ : y--;
		while (x != next_room->x && (map[x][y].flag_path = 1) == 1)
			(room->x < next_room->x) ? x++ : x--;
		if (!(room->y < next_room->y))
			while (y != next_room->y && (map[x][y].flag_path = 1) == 1)
				(room->y < next_room->y) ? y++ : y--;
		map[x][y].flag_path = 1;
		room = next_room;
	}
}

void	apply_paths_to_visualizer_map(t_global *gl)
{
	t_path		*path;
	t_room		start_room;
	t_entree	*ent;

	if (!(ent = dict_search(gl->dict, gl->start)))
		return ;
	start_room.name = "";
	start_room.x = ENT_DATA->x;
	start_room.y = ENT_DATA->y;
	path = gl->paths;
	while (path)
	{
		start_room.next = path->rooms;
		apply_specific_path_to_visualizer_map(gl, &start_room);
		path = path->next;
	}
}
