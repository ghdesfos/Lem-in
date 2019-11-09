/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:31:12 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/09 11:44:18 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
struct ant_movement
{
	current_room
	next_room
	current position
	reached
	int color_ant
	next ant_movement
}
*/

//	on ajoute un ant movement a la fin de chaque dispatch
//	
//	on pourrait creer une chain list de toutes les ants a distribuer dans le graph avec un retardateur

//	on pourrait creer un tableau du genre: ant_movement *moves[gl->nbPaths]
//	on stockerait dedans tourtes les ants

void	print_visualizer_map(t_global *gl)
{
	int i;
	int j;

	i = -1;
	while (++i < gl->maxRoomCoorX + 1)
	{
		j = -1;
		while (++j < gl->maxRoomCoorY + 1)
		{
			printw("%c", (gl->map)[i][j]);
		}
		printw("\n");
	}
}

void	print_ants_in_visualizer(t_global *gl, t_dispatch **ants, int move_nb)
{
	t_dispatch	*tmp;
	int			path_nb;

	path_nb = -1;
	while (++path_nb < gl->nb_paths)
	{
		tmp = ants[path_nb];
		while (tmp)
		{
			if (tmp->delay - move_nb > 0)
				break ;
		//	move(tmp->coor[1], tmp->coor[0]);
			move(tmp->coor[0], tmp->coor[1]);
			printw("%c", CHAR_ANT);
			tmp = tmp->next;
		}
	}
	refresh();
}

void	set_up_ants_for_visualizer(t_global *gl, t_dispatch **ants)
{
	t_entree	*ent;
	t_path		*path;
	t_dispatch	*new;
	int			path_nb;
	int			i;

	if (!(ent = dict_search(gl->dict, gl->start)))
		return ;
	path = gl->paths;
	path_nb = 0;
	while (path)
	{
		i = path->ants_to_dispatch;
		while (--i >= 0)
		{
			new = create_dispatch_elem(0, path, \
										(int[2]){ENT_DATA->x, ENT_DATA->y}, i);
			new->next = ants[path_nb];
			ants[path_nb] = new;
		}
		path_nb += 1;
		path = path->next;
	}
}

/*
**	We do a "break ;" when tmp->delay - move_nb > 0 because all following \
**	t_dispatch element are in the same case, due to how they were orderered \
**	during their creation.
**	The variable change_flag helps us know if all ants have reached their next \
**	room yet.
*/

#define COOR_X	(tmp->coor[0])
#define COOR_Y	(tmp->coor[1])

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
				// QUE SE PASSE_T_IL SI ROOM == NULL
				if (tmp->room)
				{
					if (tmp->delay - move_nb > 0)
						break ;
					if (COOR_X != tmp->room->x && (change_flag = 1) == 1)
						(COOR_X < tmp->room->x) ? COOR_X++ : COOR_X--;
					else if (COOR_Y != tmp->room->y && (change_flag = 1) == 1)
						(COOR_Y < tmp->room->y) ? COOR_Y++ : COOR_Y--;
				}
				tmp = tmp->next;
			}
		}

		//	while (1);
		print_ants_in_visualizer(gl, ants, move_nb);
		refresh();
		usleep(50000);
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
				tmp->room = tmp->room->next;
			tmp = tmp->next;
		}		
	}
}

void	launch_visualizer(t_global *gl)
{
	t_dispatch	*ants[gl->nb_paths];
	int			i;
	int			move_nb;

	// CHECK if the window is big enough for the visualizer
	// DO IT PERHAPS BEFORE BEFORE THE MALLOC OF THE MAP???
	i = -1;
	while (++i < gl->nb_paths)
		ants[i] = NULL;	
	set_up_ants_for_visualizer(gl, ants);
	initscr();
	curs_set(0);
	move_nb = 0;
	while (1)
	{
		move_ants_to_next_room_in_visualizer(gl, ants, move_nb);
		update_ants_next_room_in_visualizer(gl, ants, move_nb);
	//	if (check_all_ants_have_reached_end_visualizer(gl, ants))
	//		break ;
		move_nb++;
	}
	endwin();
	//	FREE
}
