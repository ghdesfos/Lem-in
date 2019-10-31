/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 08:58:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/27 19:49:45 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
**	To be a valid link, the line has to contain the name of 2 existing rooms \
**	separated by a '-'.
*/

int		check_existing_room_name(t_global *gl, char *roomNameToCheck)
{
	if (NULL == dict_search(gl->dict, roomNameToCheck))
		return (0);
	return (1);
}

/*
**	The function checks if we have 2 'words' that were separated by a '-'.
**	It checks if both correspond to valid room names.
**	It also checks that both names are different.
*/

int		check_valid_link(t_global *gl, char **words)
{
	if (!words)
		return (0);
	if (!(words[0]) || !(words[1]))
		return (0);
	if (words[2])
		return (0);
	if (!check_existing_room_name(gl, words[0])
			|| !check_existing_room_name(gl, words[1]))
		return (0);
	if (0 == ft_strcmp(words[0], words[1]))
		return (0);
	return (1);
}

/*
**	The return of ft_strsplit (success of the malloc) is checked inside \
**	the check_valid_link() function.
*/

int		add_link_to_dict(t_global *gl, int fd, char *line)
{
	char	**words;

	words = ft_strsplit(line, '-');
	if (!check_valid_link(gl, words))
	{
		ft_putstr_fd("ERROR\nsome links are invalid\n", STDERR_FILENO);
		free_global(gl);
		free_words(words);
		free(line);
		close(fd);
		exit(-4);
	}
	if (NULL == dict_insert(gl->dict, words[0], words[1])
			|| NULL == dict_insert(gl->dict, words[1], words[0]))
	{
		ft_putstr_fd("ERROR\nproblem with the adding of some links \
to the dictionary\n", STDERR_FILENO);
		free_global(gl);
		free_words(words);
		free(line);
		close(fd);
		exit(-4);
	}
	free_words(words);
	return (1);
}

/*
**	This functions checks that the start and the end rooms are at least \
**	connected to one link.
*/

void	check_read_link_info_results(t_global *gl, int fd)
{
	if (NULL == dict_search(gl->dict, gl->start))
	{
		ft_putstr_fd("ERROR\nthe start room is not connected to at least \
one room\n", STDERR_FILENO);
		free_global(gl);
		close(fd);
		exit (-5);
	}
	if (NULL == dict_search(gl->dict, gl->end))
	{
		ft_putstr_fd("ERROR\nthe end room is not connected to at least \
one room\n", STDERR_FILENO);
		free_global(gl);
		close(fd);
		exit (-5);
	}
}

/*
**	This function is called with a char *line which contains the last line \
**	read during the reading of the room information.
**	That's why get_next_line() is called at the end of the loop.
*/

void	read_link_info(t_global *gl, int fd, char *line)
{
	if (!line)
		return ;
	while (1)
	{
		if (!(line = ft_strtrim_free(line)))
			return ;
		if (line[0] != COMMENT_CHAR)
			add_link_to_dict(gl, fd, line);
		free(line);
		if (1 != get_next_line(fd, &line))
			return ;
		add_line_to_struct(gl, line);
	}
}
