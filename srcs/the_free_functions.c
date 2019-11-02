/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_free_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:01:22 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/01 19:11:00 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_rooms(t_room *rooms)
{
	t_room *tmp;
	t_room *next;

	if (!rooms)
		return ;
	tmp = rooms;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp);
		tmp = next;
	}
}

/*
**	We do not free the different element contained inside the ENT_DATA->values.
**	Indeed, these are entrees of the dict, and they will all be removed during \
**	the dict freeing process.
*/

void	free_entree(t_entree *ent)
{
	if (!ent)
		return ;
	if (ENT_DATA)
	{
		free(ENT_DATA->key);
		free(ENT_DATA->values);
		free(ent->data);
	}
	free(ent);
}

void	free_dict(t_dict *dict)
{
	t_entree	*curr;
	t_entree	*next;
	int			i;

	if (!dict)
		return ;
	i = -1;
	while (++i < dict->size)
	{
		curr = (dict->entrees)[i];
		while (curr)
		{
			next = curr->next;
			free_entree(curr);
			curr = next;
		}
	}
	free(dict->entrees);
	free(dict);
}

void	free_paths(t_path *paths)
{
	t_path *tmp;
	t_path *next;

	if (!paths)
		return ;
	tmp = paths;
	while (tmp)
	{
		next = tmp->next;
		free_rooms(tmp->rooms);
		free(tmp);
		tmp = next;
	}
}

void	free_global(t_global *gl)
{
	free_lines(gl->lines);
	free(gl->start);
	free(gl->end);
	free_rooms(gl->rooms);
	free_dict(gl->dict);
	free_paths(gl->paths);
}
