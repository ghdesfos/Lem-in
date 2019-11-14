/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_map_creation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:39:42 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:31:17 by ghdesfos         ###   ########.fr       */
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
	int max_x;
	int max_y;

	max_x = gl->max_room_coor_x;
	max_y = gl->max_room_coor_y;
	if (!(gl->map = (t_map_elem**)malloc(sizeof(t_map_elem*) * (max_x + 2))))
		create_visualizer_map_error_management(gl);
	i = -1;
	while (++i < max_x + 1)
		if (!((gl->map)[i] = (t_map_elem*)malloc(sizeof(t_map_elem) \
													* (max_y + 1))))
			create_visualizer_map_error_management(gl);
	(gl->map)[max_x + 1] = NULL;
	i = -1;
	while (++i < max_x + 1)
	{
		j = -1;
		while (++j < max_y + 1)
		{
			gl->map[i][j].pchar = ' ';
			gl->map[i][j].flag_path = 0;
		}
	}
}
