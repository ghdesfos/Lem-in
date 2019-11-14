/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:56:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 17:27:43 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_gl(t_global *gl)
{
	gl->options = 0;
	gl->nb_ants = 0;
	gl->lines = NULL;
	gl->nb_rooms = 0;
	gl->start = NULL;
	gl->end = NULL;
	gl->rooms = NULL;
	if (NULL == (gl->dict = dict_init(SIZE_DICT)))
		exit(-2);
	gl->paths = NULL;
	gl->nb_paths = 0;
	gl->max_path_len = 0;
	gl->dispatch_moves = 0;
	gl->max_room_coor_x = 0;
	gl->max_room_coor_y = 0;
	gl->map = NULL;
	gl->visualizer_moves = 0;
	gl->visualizer_ants_arrived = 0;
	return (0);
}

void	read_flags_error_management(t_global *gl, int flag)
{
	ft_putstr_fd(USAGE, 2);
	if (flag)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("Flag n prints the number of moves to bring all ants \
from start to end.\n", 2);
		ft_putstr_fd("Flag p prints the pathes that are used \
for the dispatch.\n", 2);
		ft_putstr_fd("Flag q makes the program run in quiet mode, only \
the ants moves are printed.\n", 2);
		ft_putstr_fd("Flag v launches the visualizer.\n", 2);
	}
	free_global(gl);
	exit(-1);
}

void	read_flags(t_global *gl, int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	while (++i < argc)
	{
		if (0 == ft_strcmp(argv[i], "--help"))
			read_flags_error_management(gl, 1);
		if (argv[i][0] != '-' || (argv[i][0] == '-' && argv[i][1] == 0))
			read_flags_error_management(gl, 0);
		j = 0;
		while (argv[i][++j])
		{
			if (NULL == ft_strchr(FLAGS, argv[i][j]))
				read_flags_error_management(gl, 0);
			if ('n' == argv[i][j])
				gl->options |= FLAG_N;
			else if ('p' == argv[i][j])
				gl->options |= FLAG_P;
			else if ('q' == argv[i][j])
				gl->options |= FLAG_Q;
			else if ('v' == argv[i][j])
				gl->options |= FLAG_V;
		}
	}
}

/*
**	We print the lines from the input file after the function find_paths() \
**	has returned, because this is at this time we have done all necessary \
**	error management.
**	You can call the print_global(&gl) function if you want to print \
**	the struct gl before it gets freed.
*/

int		main(int argc, char **argv)
{
	t_global gl;

	init_gl(&gl);
	read_flags(&gl, argc, argv);
	read_input(&gl);
	find_paths(&gl);
	if (!(FLAG_Q & gl.options))
		print_input_file_lines(gl.lines);
	dispatch_ants_through_paths(&gl);
	if (FLAG_P & gl.options)
		print_paths(gl.paths);
	if (FLAG_N & gl.options)
		print_total_moves(&gl);
	if (FLAG_V & gl.options)
		launch_visualizer(&gl);
	free_global(&gl);
	return (0);
}
