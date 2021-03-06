/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_print_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:30:28 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 17:50:07 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_char_in_color(char c, int color_pair, int bold)
{
	if (bold)
		attron(A_BOLD);
	attron(COLOR_PAIR(color_pair));
	printw("%c", c);
	attroff(COLOR_PAIR(color_pair));
	if (bold)
		attroff(A_BOLD);
}

void	print_visualizer_map(t_global *gl)
{
	t_map_elem	**map;
	int			i;
	int			j;
	char		c;

	map = gl->map;
	i = -1;
	while (++i < gl->max_room_coor_x + 1)
	{
		j = -1;
		while (++j < gl->max_room_coor_y + 1)
		{
			c = map[i][j].pchar;
			if (c == CHAR_SOURCE)
				print_char_in_color(c, C_PAIR_BLUE, 1);
			else if (c == CHAR_SINK)
				print_char_in_color(c, C_PAIR_GREEN, 1);
			else if (1 == map[i][j].flag_path)
				print_char_in_color(c, C_PAIR_WHITE, 1);
			else
				print_char_in_color(c, C_PAIR_WHITE, 0);
		}
		printw("\n");
	}
}

void	print_dispatch_information(t_global *gl)
{
	move(gl->max_room_coor_x + 1, 0);
	printw("\nAnts Arrived: %d    Steps: %d\n", gl->visualizer_ants_arrived, \
													gl->visualizer_moves);
	attron(A_BOLD);
	attron(COLOR_PAIR(C_PAIR_BLUE));
	printw("\nS  -->  source of the graph (start room)\n");
	attroff(COLOR_PAIR(C_PAIR_BLUE));
	attron(COLOR_PAIR(C_PAIR_GREEN));
	printw("T  -->  sink of the graph (end room)\n");
	attroff(COLOR_PAIR(C_PAIR_GREEN));
	attron(COLOR_PAIR(C_PAIR_WHITE));
	printw("R  -->  other used rooms of the graph\n");
	attroff(COLOR_PAIR(C_PAIR_WHITE));
	attroff(A_BOLD);
	attron(COLOR_PAIR(C_PAIR_WHITE));
	printw("R  -->  other non-used rooms of the graph\n");
	attroff(COLOR_PAIR(C_PAIR_WHITE));
	attron(A_BOLD);
	attron(COLOR_PAIR(C_PAIR_WHITE));
	printw("@  -->  ants (odd number yellow, even red)\n");
	attroff(COLOR_PAIR(C_PAIR_WHITE));
	attroff(A_BOLD);
	refresh();
	usleep(TIME_BTW_MOVES);
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
			if (tmp->room)
			{
				move(tmp->coor[0], tmp->coor[1]);
				if (tmp->delay % 2 == 0)
					print_char_in_color(CHAR_ANT, C_PAIR_YELLOW, 1);
				else
					print_char_in_color(CHAR_ANT, C_PAIR_RED, 1);
			}
			tmp = tmp->next;
		}
	}
	refresh();
	usleep(ANT_SPEED);
}
