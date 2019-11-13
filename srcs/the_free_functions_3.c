/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_free_functions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:35:34 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/12 21:19:42 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_visualizer_map(t_global *gl, t_map_elem **map)
{
	int i;

	i = -1;
	if (map && map[0])
		while (++i < gl->max_room_coor_x + 1)
			free(map[i]);
	free(map);
}
