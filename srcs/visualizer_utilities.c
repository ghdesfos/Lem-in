/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:00:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/09 11:47:03 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_max_room_coordinates(t_global *gl, t_entree *ent)
{
	if (ENT_DATA->x > gl->maxRoomCoorX)
		gl->maxRoomCoorX = ENT_DATA->x;
	if (ENT_DATA->y > gl->maxRoomCoorY)
		gl->maxRoomCoorY = ENT_DATA->y;
}
