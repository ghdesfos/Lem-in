/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_map_creation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:39:42 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/09 11:56:59 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	create_visualizer_map_error_management(t_global *gl)
{
	ft_putstr_fd("Problem with the malloc of the visualizer map.\n", 2);
	free_global(gl);
	exit(-10);
}

void	create_visualizer_map(t_global *gl)
{
	int i;
	int j;
	int maxX;
	int maxY;

	maxX = gl->maxRoomCoorX;
	maxY = gl->maxRoomCoorY;
	if (!(gl->map = (t_map_elem**)malloc(sizeof(t_map_elem*) * (maxX + 2))))
		create_visualizer_map_error_management(gl);
	i = -1;
	while (++i < gl->maxRoomCoorX + 1)
		if (!((gl->map)[i] = (t_map_elem*)malloc(sizeof(t_map_elem) \
													* (maxY + 1))))
			create_visualizer_map_error_management(gl);
	(gl->map)[maxX + 1] = NULL;
	i = -1;
	while (++i < gl->maxRoomCoorX + 1)
	{
		j = -1;
		while (++j < gl->maxRoomCoorY + 1)
		{
			gl->map[i][j].pchar = ' ';
			gl->map[i][j].flag_path = 0;
		}
	}
}
