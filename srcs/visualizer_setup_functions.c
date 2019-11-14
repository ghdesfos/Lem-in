/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_setup_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 22:10:15 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 17:24:58 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	For some reason, we had to call two times init_pair for the blue color, \
**	otherwise it would not work...
**	Must be due to some specificities of the ncurses implementation.
*/

void	visualizer_color_error_management(t_global *gl)
{
	ft_putstr_fd("ERROR\nyour terminal does not support color \
what is necessary for the visualizer...\n", STDERR_FILENO);
	free_global(gl);
	exit(-12);
}

void	set_up_ncurses_environment(t_global *gl)
{
	initscr();
	curs_set(0);
	start_color();
	if (!can_change_color())
		visualizer_color_error_management(gl);
	init_pair(C_PAIR_BLUE, BLUE, BLACK);
	init_pair(C_PAIR_BLUE, BLUE, BLACK);
	init_pair(C_PAIR_GREEN, GREEN, BLACK);
	init_pair(C_PAIR_YELLOW, YELLOW, BLACK);
	init_pair(C_PAIR_RED, RED, BLACK);
	init_pair(C_PAIR_WHITE, WHITE, BLACK);
}

void	end_ncurses_environment(t_global *gl)
{
	print_dispatch_information(gl);
	attron(COLOR_PAIR(C_PAIR_GREEN));
	printw("\nAll ants have reached the sink! Thanks for watching!\n");
	attroff(COLOR_PAIR(C_PAIR_GREEN));
	attron(COLOR_PAIR(C_PAIR_YELLOW));
	printw("All ants mean %d ants, and they took a total of \
%d moves to reach the sink, using %d path(s)... :)", \
				gl->nb_ants, gl->dispatch_moves, gl->nb_paths);
	attroff(COLOR_PAIR(C_PAIR_YELLOW));
	refresh();
	sleep(TIME_CLOSE_VIS);
	endwin();
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
