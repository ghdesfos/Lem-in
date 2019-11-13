/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:31:12 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/12 21:34:10 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	We do a "break ;" when tmp->delay - move_nb > 0 because all following \
**	t_dispatch element are in the same case, due to how they were orderered \
**	during their creation.
**	The variable change_flag helps us know if all ants have reached their next \
**	room yet.
**
**	In the subfunction, we want to print the path starting at the leftest room \
**	drawing first an horizontal line and then the vertical line.
**	This way, it will be coherent to the way we drawed the paths \
**	in the functions:
**	- add_link_elements_to_visualizer_map()
**	- apply_specific_path_to_visualizer_map()
*/

#define COOR_X	(tmp->coor[0])
#define COOR_Y	(tmp->coor[1])

void	move_ants_to_next_room_in_visualizer_sub(t_dispatch *tmp, \
													int *change_flag)
{
	if (COOR_Y < tmp->room->y)
	{
		if (COOR_Y != tmp->room->y && (*change_flag = 1) == 1)
			(COOR_Y < tmp->room->y) ? COOR_Y++ : COOR_Y--;
		else if (COOR_X != tmp->room->x && (*change_flag = 1) == 1)
			(COOR_X < tmp->room->x) ? COOR_X++ : COOR_X--;
	}
	else
	{
		if (COOR_X != tmp->room->x && (*change_flag = 1) == 1)
			(COOR_X < tmp->room->x) ? COOR_X++ : COOR_X--;
		else if (COOR_Y != tmp->room->y && (*change_flag = 1) == 1)
			(COOR_Y < tmp->room->y) ? COOR_Y++ : COOR_Y--;
	}
}

void	move_ants_to_next_room_in_visualizer(t_global *gl, t_dispatch **ants, \
											int move_nb)
{
	t_dispatch	*tmp;
	int			path_nb;
	int			change_flag;

	change_flag = 1;
	while (change_flag)
	{
		change_flag = 0;
		move(0, 0);
		print_visualizer_map(gl);
		path_nb = -1;
		while (++path_nb < gl->nb_paths)
		{
			tmp = ants[path_nb];
			while (tmp)
			{
				if (tmp->delay - move_nb > 0)
					break ;
				if (tmp->room)
					move_ants_to_next_room_in_visualizer_sub(tmp, &change_flag);
				tmp = tmp->next;
			}
		}
		print_ants_in_visualizer(gl, ants, move_nb);
	}
}

void	update_ants_next_room_in_visualizer(t_global *gl, t_dispatch **ants, \
												int move_nb)
{
	t_dispatch	*tmp;
	int			path_nb;

	path_nb = -1;
	while (++path_nb < gl->nb_paths)
	{
		tmp = ants[path_nb];
		while (tmp)
		{
			if (tmp->delay - move_nb <= 0 && tmp->room)
			{
				tmp->room = tmp->room->next;
				if (NULL == tmp->room)
					gl->visualizer_ants_arrived += 1;
			}
			tmp = tmp->next;
		}
	}
}

void	launch_visualizer(t_global *gl)
{
	t_dispatch	*ants[gl->nb_paths];
	int			i;
	int			move_nb;

	check_window_size_for_visualizer(gl);
	i = -1;
	while (++i < gl->nb_paths)
		ants[i] = NULL;
	set_up_ncurses_environment(gl);
	set_up_ants_for_visualizer(gl, ants);
	move_nb = 0;
	while (1)
	{
		print_dispatch_information(gl);
		move_ants_to_next_room_in_visualizer(gl, ants, move_nb);
		if (check_all_ants_have_reached_end_visualizer(gl, ants))
			break ;
		update_ants_next_room_in_visualizer(gl, ants, move_nb);
		gl->visualizer_moves += 1;
		move_nb++;
	}
	end_ncurses_environment(gl);
	free_dispatchs(ants, gl->nb_paths, 0);
}
