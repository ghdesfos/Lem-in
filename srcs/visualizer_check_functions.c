/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_check_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 21:01:58 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/12 16:47:50 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	The macro getmaxyx put unexpected values into window_height and \
**	window_width causing the program to exit.
**	That's why we added a if (1) condition in order to keep this function \
**	in case but not have it exit the program.
*/

void	check_window_size_for_visualizer(t_global *gl)
{
	int window_width;
	int window_height;

	getmaxyx(stdscr, window_width, window_height);
	if (window_width >= gl->max_room_coor_y + 1
			&& window_height >= gl->max_room_coor_x + 1)
		return ;
	else if (1)
		return ;
	else
	{
		ft_putstr_fd("ERROR\nyour terminal window is not \
big enough\n", STDERR_FILENO);
		b_printf("it has to be at least %d characters wide and %d characters \
high in order to display the visualizer", \
					gl->max_room_coor_y + 1, gl->max_room_coor_x + 1);
		free_global(gl);
		exit(-11);
	}
}

int		check_all_ants_have_reached_end_visualizer(t_global *gl, \
											t_dispatch **ants)
{
	t_dispatch	*tmp;
	int			path_nb;

	path_nb = -1;
	while (++path_nb < gl->nb_paths)
	{
		tmp = ants[path_nb];
		while (tmp)
		{
			if (tmp->room)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}
