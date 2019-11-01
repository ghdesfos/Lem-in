/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_room_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 08:56:17 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 18:19:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	This functions allows to add the room name to the rooms list.
**	This list is then used for some error management.
*/

int		add_room_to_rooms_list(t_global *gl, char **words)
{
	t_room	*new_room;

	if (!(new_room = (t_room*)malloc(sizeof(t_room))))
		return (-1);
	new_room->name = ft_strdup(words[0]);
	new_room->x = ft_atoi(words[1]);
	new_room->y = ft_atoi(words[2]);
	new_room->next = gl->rooms;
	gl->rooms = new_room;
	return (1);
}

/*
**	The function returns 0, when the line did not contain the information \
**	necessary to construct a room.
**	The return of ft_strsplit (success of the malloc) is checked inside \
**	the check_valid_room() function.
*/

int		add_room_to_dict(t_global *gl, char *line, int room_type)
{
	t_entree	*ent;
	char		**words;

	words = ft_strsplit(line, ' ');
	if (!check_valid_room(words))
	{
		free_words(words);
		return (0);
	}
	if (NULL == (ent = dict_insert(gl->dict, words[0], NULL))
		|| -1 == add_room_to_rooms_list(gl, words))
	{
		free_words(words);
		return (-1);
	}
	if (room_type == START_ROOM)
		gl->start = ft_strdup(words[0]);
	else if (room_type == END_ROOM)
		gl->end = ft_strdup(words[0]);
	ENT_DATA->x = ft_atoi(words[1]);
	ENT_DATA->y = ft_atoi(words[2]);
	(gl->nb_rooms)++;
	free_words(words);
	return (1);
}

/*
**	If flagStart or flagEnd are different than 0, it means that there has \
**	always been another start or end room defined, hence the error manag.
*/

void	start_line_flag_management(t_global *gl, int fd, char *line, \
									int *flag_start)
{
	if (*flag_start == 0)
		(*flag_start)++;
	else
		read_room_info_error_management(gl, fd, line, START_ROOM_ERR);
}

void	end_line_flag_management(t_global *gl, int fd, char *line, \
									int *flag_end)
{
	if (*flag_end == 0)
		(*flag_end)++;
	else
		read_room_info_error_management(gl, fd, line, END_ROOM_ERR);
}

/*
**	The function below is called with the values 0 for flags[0] (flag start) \
**	and flags[1] (flag 1).
**	If we have a comment, we just free the line and move on to next line.
**	When flag start == 1 or flag end == 1, we do ++, in order to not reinter \
**	these conditions a second time.
**	When the line is not a valid room, nor a comment, the function returns \
**	It thus has to be the first line describing a link between rooms.
**	The value of this first non-room line is stored in char **line.
*/

void	read_room_info(t_global *gl, int fd, char **line, int *flags)
{
	while (1 == get_next_line(fd, line) && add_line_to_struct(gl, *line)
			&& (*line = ft_strtrim_free(*line)))
	{
		if (0 == ft_strcmp(*line, STR_START))
			start_line_flag_management(gl, fd, *line, &(flags[0]));
		else if (0 == ft_strcmp(*line, STR_END))
			end_line_flag_management(gl, fd, *line, &(flags[1]));
		else if (flags[0] == 1 && flags[1] == 1)
			read_room_info_error_management(gl, fd, *line, ST_AND_END_ERR);
		else if (flags[0] == 1 && (*line)[0] != COMMENT_CHAR)
		{
			if ((flags[0])++ && !add_room_to_dict(gl, *line, START_ROOM))
				return ;
		}
		else if (flags[1] == 1 && (*line)[0] != COMMENT_CHAR)
		{
			if ((flags[1])++ && !add_room_to_dict(gl, *line, END_ROOM))
				return ;
		}
		else if ((*line)[0] != COMMENT_CHAR)
			if (!add_room_to_dict(gl, *line, NORMAL_ROOM))
				return ;
		free(*line);
	}
	*line = NULL;
}
