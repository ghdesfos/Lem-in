/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:56:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/26 19:01:18 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// S'il n'y a pas de path reliant start to end, message d'erreur
// Revoir tous les close() car apres tout on lit a partir du std output...

// probleme si on ne passe pas de fichier et ensuite fait control+D --> pointer being freed was not allocated

int		init_gl(t_global *gl)
{
	gl->nbAnts = 0;
	gl->start = NULL;
	gl->end = NULL;
	gl->rooms = NULL;
	if (NULL == (gl->dict = dict_init(SIZE_DICT)))
		return (-1);
	gl->paths = NULL;
	return (0);
}

// ajouter un close() si jamais on change l'input de STD_OUTPUT?
// a priori il faut supprimer cette fonction car on ne peut pas lire deux fois,
// ce qui vient du standard input

/*
int		pre_test_input_file(void)
{
	char	*line;
	int		countStart;
	int		countEnd;

	countStart = 0;
	countEnd = 0;
	while (1 == get_next_line(FD, &line))
	{
		if (0 == ft_strcmp(line, STR_START))
			countStart++;
		if (0 == ft_strcmp(line, STR_END))
			countEnd++;
		free(line);
	}
	if (countStart != 1)
		ft_putstr_fd("ERROR\nnot the right number of start chamber, \
						it should be one\n", STDERR_FILENO);
	if (countEnd != 1)
		ft_putstr_fd("ERROR\nnot the right number of end chamber, \
						it should be one\n", STDERR_FILENO);
	if (countStart != 1 || countEnd != 1)
		return (-1);
	return (0);
}
*/

int		main(void)
{
	t_global gl;

	b_printf("test1\n");
/*	if (-1 == pre_test_input_file())
		return (-1); */

	b_printf("test2\n");
	if (-1 == init_gl(&gl))
		return (-2);

	b_printf("test3\n");
	if (-1 == read_input(&gl))
		return (-3);

	b_printf("test3\n");
	print_global(&gl);

//	if (-1 == find_paths(&gl))
//		return (-4);
//	dispatch_ants_through_paths(&gl);
	free_global(&gl);

	while (1);
	return (0);
}
