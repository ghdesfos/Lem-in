/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:00:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:33:49 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_max_room_coordinates(t_global *gl, t_entree *ent)
{
	if (ENT_DATA->x > gl->max_room_coor_x)
		gl->max_room_coor_x = ENT_DATA->x;
	if (ENT_DATA->y > gl->max_room_coor_y)
		gl->max_room_coor_y = ENT_DATA->y;
}

void	swap_coordinates(int *coor1, int *coor2)
{
	int tmp;

	tmp = coor1[0];
	coor1[0] = coor2[0];
	coor2[0] = tmp;
	tmp = coor1[1];
	coor1[1] = coor2[1];
	coor2[1] = tmp;
}
