/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:56:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/25 15:43:00 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

// S'il n'y a pas de path reliant start to end, message d'erreur

int		init_gl(t_global *gl)
{
	gl->nbAnts = 0;
	gl->start = NULL;
	gl->end = NULL;
	gl->rooms = NULL;
	if (NULL = (gl->dict = dict_init(SIZE_DICT))
		return (-1);
	gl->paths = NULL;
	return (0);
}

int		pre_test_input_file(void)
{
	char	*line;
	int		countStart;
	int		countEnd;

	countStart = 0;
	countEnd = 0;
	while (1 == get_next_line(STDOUT_FILENO, &line))
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
	if (-1 == close(fd) || countStart != 1 || countEnd != 1)
		return (-1);
	return (0);
}

int		main(void)
{
	t_global gl;

	if (-1 == pre_test_input_file())
		return (-1);
	if (-1 == init_gl(&gl))
		return (-2);
	if (-1 == read_input(&gl))
		return (-3);
	if (-1 == find_paths(&gl))
		return (-4);
	dispatch_ants_through_paths(&gl);
	free_global(&gl);
	return (0);
}
