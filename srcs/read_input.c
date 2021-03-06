/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 08:53:40 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:20:32 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	We store inside of line, the last line read during the reading of \
**	the room info, as this last line is the first that may contain \
**	link info, which is why it is pushed to read_link_info().
*/

void	read_input(t_global *gl)
{
	int		fd;
	char	*line;

	fd = FD;
	line = NULL;
	read_ants_number(gl, fd);
	read_room_info(gl, fd, &line, (int[2]){0, 0});
	check_read_room_info_results(gl, fd, line);
	if (FLAG_V & gl->options)
	{
		create_visualizer_map(gl);
		add_rooms_to_visualizer_map(gl);
	}
	read_link_info(gl, fd, line);
	close(fd);
}
