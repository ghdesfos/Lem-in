/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room_info_error_management.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:08:03 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/07 15:17:56 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	We check if the line has 3 "words", the first one is a string that \
**	does not start with COMMENT_CHAR or SOLUTION_CHAR, and that the second \
**	and the third one correspond to positive int.
*/

int		check_valid_room(char **words)
{
	if (!words)
		return (0);
	if (!(words[0]) || !(words[1]) || !(words[2]))
		return (0);
	if (words[3])
		return (0);
	if (words[0][0] == COMMENT_CHAR || words[0][0] == SOLUTION_CHAR)
		return (0);
	if (0 > check_is_a_positive_int(words[1]))
		return (0);
	if (0 > check_is_a_positive_int(words[2]))
		return (0);
	return (1);
}

void	read_room_info_error_management(t_global *gl, int fd, char *line, \
											int error_nb)
{
	ft_putstr_fd("ERROR\n", STDERR_FILENO);
	if (error_nb == START_ROOM)
		ft_putstr_fd("the number of start room flags is superior to one\n", \
						STDERR_FILENO);
	else if (error_nb == END_ROOM)
		ft_putstr_fd("the number of end room flags is superior to one\n", \
						STDERR_FILENO);
	else if (error_nb == ST_AND_END_ERR)
		ft_putstr_fd("the start and end room flags apply to the same room\n", \
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

int		check_all_rooms_have_different_coordinates(t_global *gl)
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
			if (tmp->x == tmp2->x && tmp->y == tmp2->y)
				return (0);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

/*
**	This function checks that we have a start and an end room.
**	It also checks if we did not have 2 different rooms with the same name.
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
		exit(-3);
	}
	if (!check_all_rooms_have_different_names(gl)
			|| !check_all_rooms_have_different_coordinates(gl))
	{
		ft_putstr_fd("ERROR\n", STDERR_FILENO);
		if (!check_all_rooms_have_different_names(gl))
			ft_putstr_fd("there were 2 rooms with the same name\n", \
						STDERR_FILENO);
		else
			ft_putstr_fd("there were 2 rooms with the same coordinates\n", \
						STDERR_FILENO);
		free_global(gl);
		close(fd);
		free(line);
		exit(-3);
	}
}
