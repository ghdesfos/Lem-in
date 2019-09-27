/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 08:56:17 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/27 11:25:14 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

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

/*
**	The function returns 0, when the line did not contain the information \
**	necessary to construct a room.
**	The return of ft_strsplit (success of the malloc) is checked inside \
**	the check_valid_room() function.
**	If the newRoom malloc fails, the room will simply not be added to \
**	the room list.
*/

int		add_room_to_list(t_global *gl, char *line, int roomType)
{
	t_room	*newRoom;
	char	**words;

	words = ft_strsplit(line, ' ');
	if (!check_valid_room(words))
	{
		free_words(words);
		return (0);
	}
	if (roomType == START_ROOM)
		gl->start = ft_strdup(words[0]);
	else if (roomType == END_ROOM)
		gl->end = ft_strdup(words[0]);
	if (!(newRoom = (t_room*)malloc(sizeof(t_room))))
		return (-1);
	newRoom->name = ft_strdup(words[0]);
	newRoom->x = ft_atoi(words[1]);
	newRoom->y = ft_atoi(words[2]);
	newRoom->next = gl->rooms;
	gl->rooms = newRoom;
	free_words(words);
	return (1);
}

/*
**	If flagStart or flagEnd are different than 0, it means that there has \
**	always been another start or end room defined, hence the error manag.
*/

void	start_line_flag_management(t_global *gl, int fd, char *line, \
									int *flagStart)
{
	if (*flagStart == 0)
		(*flagStart)++;
	else
		read_room_info_error_management(gl, fd, line, START_ROOM);
}

void	end_line_flag_management(t_global *gl, int fd, char *line, \
									int *flagEnd)
{
	if (*flagEnd == 0)
		(*flagEnd)++;
	else
		read_room_info_error_management(gl, fd, line, END_ROOM);
}

/*
**	The function below is called with the values 0 for flagStart and flagEnd.
**	If we have a comment, we just free the line and move on to next line.
**	When flagStart == 1 or flagEnd == 1, we do ++, in order to not reinter \
**	these conditions a second time.
**	We do return (line) when the line is not a valid room, nor a comment, \
**	It thus has to be thr first line describing a link between rooms.
*/

char	*read_room_info(t_global *gl, int fd, int flagStart, int flagEnd)
{
	char *line;

	while (1 == get_next_line(fd, &line) && (line = ft_strtrim_free(line)))
	{
		if (0 == ft_strcmp(line, STR_START))
			start_line_flag_management(gl, fd, line, &flagStart);
		else if (0 == ft_strcmp(line, STR_END))
			end_line_flag_management(gl, fd, line, &flagEnd);
		else if (flagStart == 1 && line[0] != COMMENT_CHAR)
		{
			if (flagStart++ && !add_room_to_list(gl, line, START_ROOM))
				return (line);
		}
		else if (flagEnd == 1 && line[0] != COMMENT_CHAR)
		{
			if (flagEnd++ && !add_room_to_list(gl, line, END_ROOM))
				return (line);
		}
		else if (line[0] != COMMENT_CHAR)
			if (!add_room_to_list(gl, line, NORMAL_ROOM))
				return (line);
		free(line);
	}
	return (NULL);
}
