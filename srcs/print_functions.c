/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 09:44:45 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/28 20:22:58 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_rooms(t_room *rooms)
{
	t_room *tmp;

	tmp = rooms;
	b_printf("PRINTING OF THE ROOMS:\n");
	while (tmp)
	{
		b_printf("Room name %s, x %d, y %d\n", tmp->name, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	b_printf("\n");
}

void	print_entrees(t_entree **entrees)
{
	t_entree	*ent;
	char		*connectedEntreeName;
	int			i;

	if (!entrees)
		return ;
	ent = *entrees;
	while (ent)
	{
		b_printf("Key %s --> ", ENT_DATA->key);
		i = -1;
		b_printf("NB VALUES %d ADDRESS %p\n", ENT_DATA->nbValues, ENT_DATA->values);
		while (++i < ENT_DATA->nbValues)
		{
			connectedEntreeName = ((t_keyvalue*)(((ENT_DATA->values)[i])->data))->key;
			b_printf("value: %s, ", connectedEntreeName);
		}
		ent = ent->next;
	}
	b_printf("\n");
}

void	print_dict(t_dict *dict)
{
	int i;

	if (!dict)
		return ;
	b_printf("\nPRINTING OF THE DICT\n");
	b_printf("Dict size: %d\n", dict->size);
	i = -1;
	while (++i < dict->size)
	{
		if ((dict->entrees)[i])
		{
			b_printf("\nDict rk: %d:\n", i);
			print_entrees(ENT_NB(i));
		}
	}
}

void	print_paths(t_path *paths)
{
	t_path	*path;
	t_room	*room;
	int		count;

	if (!paths)
		return ;
	b_printf("\n\nPRINTING OF THE PATHS\n");
	path = paths;
	count = 0;
	while (path && ++count)
		path = path->next;
	b_printf("Number of paths: %d\n", count);
	path = paths;
	count = 0;
	while (path && ++count)
	{
		b_printf("\nPath Number: %d --> len: %d\n", count - 1, path->len);
		room = path->rooms;
		while (room)
		{
			b_printf("Room name %s\n", room->name);
			room = room->next;
		}
		path = path->next;
	}
}

void	print_global(t_global *gl)
{
	b_printf("Start room %s\n", gl->start);
	b_printf("End room %s\n", gl->end);
	print_rooms(gl->rooms);
	print_dict(gl->dict);
	print_paths(gl->paths);
}
