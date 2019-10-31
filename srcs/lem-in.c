/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:56:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 20:05:26 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// S'il n'y a pas de path reliant start to end, message d'erreur
// Revoir tous les close() car apres tout on lit a partir du std output...

// probleme si on ne passe pas de fichier et ensuite fait control+D --> pointer being freed was not allocated

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
*/

int		main(void)
{
	t_global gl;

//	b_printf("test1\n");
//	b_printf("test2\n");
	if (-1 == init_gl(&gl))
		return (-1);

//	b_printf("test3\n");
	read_input(&gl);

//	b_printf("test4\n");
	find_paths(&gl);

//	b_printf("test5\n");
	print_input_file_lines(gl.lines);
	b_printf("\n");

//	print_global(&gl);
//	b_printf("test6\n");
	dispatch_ants_through_paths(&gl);

	free_global(&gl);
	while (1);
	return (0);
}
