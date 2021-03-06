/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 08:58:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:24:58 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_existing_room_name(t_global *gl, char *room_name_to_check)
{
	if (NULL == dict_search(gl->dict, room_name_to_check))
		return (0);
	return (1);
}

/*
**	The function checks if we have 2 'words' that are separated by a '-'.
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
		close(fd);
		read_link_info_error_management(gl, words, line, 0);
	}
	if (NULL == dict_insert(gl->dict, words[0], words[1])
			|| NULL == dict_insert(gl->dict, words[1], words[0]))
	{
		close(fd);
		read_link_info_error_management(gl, words, line, 1);
	}
	if (FLAG_V & gl->options)
		add_link_to_visualizer_map(gl, words);
	free_words(words);
	return (1);
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
