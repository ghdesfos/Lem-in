/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ants_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:09:02 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:18:07 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	read_ants_number_error_management(t_global *gl, int fd)
{
	ft_putstr_fd("ERROR\n", STDERR_FILENO);
	ft_putstr_fd("the number of ants is not a valid strictly positive int\n", \
					STDERR_FILENO);
	free_global(gl);
	close(fd);
	exit(-1);
}

/*
**	We move to the first line which is not a comment, this has to be the line \
**	which contains the number of ants.
**	If this is not a valid positive int (or there was a problem with \
**	ft_strtrim_free()), we exit the program.
*/

void	read_ants_number(t_global *gl, int fd)
{
	char	*line;
	int		nb_ants;

	while (1 == get_next_line(fd, &line)
			&& add_line_to_struct(gl, line))
	{
		if (NULL == (line = ft_strtrim_free(line)))
			break ;
		if (line[0] == COMMENT_CHAR)
			free(line);
		else
			break ;
	}
	if (1 > (nb_ants = check_is_a_positive_int(line)))
	{
		free(line);
		read_ants_number_error_management(gl, fd);
	}
	gl->nb_ants = nb_ants;
	free(line);
}
