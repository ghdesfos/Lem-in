/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:56:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 17:25:36 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		init_gl(t_global *gl)
{
	gl->nbAnts = 0;
	gl->lines = NULL;
	gl->nbRooms = 0;
	gl->start = NULL;
	gl->end = NULL;
	gl->rooms = NULL;
	if (NULL == (gl->dict = dict_init(SIZE_DICT)))
		return (-1);
	gl->paths = NULL;
	gl->nbPaths = 0;
	gl->minPathLen = 0;
	gl->maxPathLen = 0;
	return (0);
}

/*
**	We print the lines from the input file after the function find_paths() \
**	has returned, because this is at this time we have done all necessary \
**	error management.
**	You can call the print_global(&gl) function if you want to print \
**	the struct gl before it gets freed.
*/

int		main(void)
{
	t_global gl;

	if (-1 == init_gl(&gl))
		return (-1);
	read_input(&gl);
	find_paths(&gl);
	print_input_file_lines(gl.lines);
	b_printf("\n");
	dispatch_ants_through_paths(&gl);
	free_global(&gl);

	while (1);
	return (0);
}
