/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room_info_error_management.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:08:03 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/25 16:29:31 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	read_room_info_error_management(t_global *gl, int fd, char *line, \
											int errorNb)
{
	ft_putstr_fd("ERROR\n", STDERR_FILENO);
	if (errorNb == START_ROOM)
		ft_putstr_fd("the number of start room flag is superior to one\n", \
						STDERR_FILENO);
	else if (errorNb == END_ROOM)
		ft_putstr_fd("the number of end room flag is superior to one\n", \
						STDERR_FILENO);
	free_global(gl);
	close(fd);
	free(line);
	exit(-2);
}

int		check_all_rooms_have_different_names(t_global *gl)
{
	t_room *tmp;
	t_room *tmp2;

	tmp = gl->rooms;
	while (tmp)
	{
		if (tmp->next)
			tmp2 = tmp->next;
		while (tmp2)
		{
			if (0 == ft_strcmp(tmp->name, tmp2->name))
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

/*
**	This function checks that we have a start and an end room.
**	It also checks if we did not have 2 idifferent rooms with the same name.
*/

void	check_read_room_info_results(t_global *gl, int fd, char *line)
{
	if (gl->start == NULL || gl->end == NULL)
	{
		ft_putstr_fd("ERROR\n", STDERR_FILENO);
		ft_putstr_fd("there was no start or end room in the input\n", \
						STDERR_FILENO);
		free_global(gl);
		close(fd);
		free(line);
		exit (-3);
	}
	if (!check_all_rooms_have_different_names(t_global *gl))
	{
		ft_putstr_fd("ERROR\n", STDERR_FILENO);
		ft_putstr_fd("there were 2 rooms with the same name\n", \
						STDERR_FILENO);
		free_global(gl);
		close(fd);
		free(line);
		exit (-3);
	}
}
