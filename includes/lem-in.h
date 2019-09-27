/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:57:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/27 11:18:47 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H



# include <stdio.h>



# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "b_printf.h"

/*
**	nbAnts is the number of ants to bring from the start to the end point.
**	rooms is the list of rooms that constitue the graph.
**	start contains the name of the room where the ants start.
**	end contains the name of the roo, where the ants finish.
**	dict contains for each room the list of rooms that are linked to it, \
**	in other words it contains the edge information of the graph.
**	paths contains the list of paths we will use to dispatch the ants from \
**	the start to the end the most rapidly possible.
*/

typedef					struct s_global
{
	int					nbAnts;
	char				*start;
	char				*end;
	struct s_room		*rooms;
	struct s_dict		*dict;
	struct s_path		*paths;
}						t_global;

typedef					struct s_room
{
	char				*name;
	int					x;
	int					y;
	struct s_room		*next;
}						t_room;

/*
**	size is the number of the dictionary.
**	entrees will contain a table .
*/

typedef					struct s_dict
{
	int					size;
	struct s_entree		**entrees;
}						t_dict;

typedef					struct s_entree
{
	void				*data;
	struct s_entree		*next;
}						t_entree;

typedef					struct s_keyvalue
{
	char				*key;
	char				**values;
}						t_keyvalue;

typedef					struct s_path
{
	struct s_room		*rooms;
	int					len;
	struct s_path		*next;
}						t_path;

# define SIZE_DICT		1000

# define COMMENT_CHAR	'#'
# define SOLUTION_CHAR	'L'
# define STR_START		"##start"
# define STR_END		"##end"
# define NORMAL_ROOM	0
# define START_ROOM		1
# define END_ROOM		2

# define ENT_DATA		((t_keyvalue*)(ent->data))
# define ENT_NB(i)		(&((dict->entrees)[i]))

# define FD				0

/*
**	Initialization functions
*/

int		init_gl(t_global *gl);
int		pre_test_input_file(void);

/*
**	Input reading functions
*/

int		check_contains_just_digits(char *line);
int		check_is_a_positive_int(char *line);

int		read_input(t_global *gl);

void	read_ants_number_error_management(t_global *gl, int fd);
void	read_ants_number(t_global *gl, int fd);

int		check_valid_room(char **words);
int		add_room_to_list(t_global *gl, char *line, int roomType);
void	start_line_flag_management(t_global *gl, int fd, char *line, \
									int *flagStart);
void	end_line_flag_management(t_global *gl, int fd, char *line, \
									int *flagEnd);
char	*read_room_info(t_global *gl, int fd, int flagStart, int flagEnd);

void	read_room_info_error_management(t_global *gl, int fd, char *line, \
											int errorNb);
int		check_all_rooms_have_different_names(t_global *gl);
int		check_all_rooms_have_different_coordinates(t_global *gl);
void	check_read_room_info_results(t_global *gl, int fd, char *line);

int		dict_insert(t_dict *dict, char *key, char *value);
char	**dict_search(t_dict *dict, char *key);
t_dict	*dict_init(int capacity);

size_t		hash(unsigned char *input);
int			add_value_to_entree(t_entree *ent, char *value);
t_entree	*create_new_entree(t_entree **entrees, char *key);
t_entree	*find_entree(t_entree **entrees, char *key);

int		check_existing_room_name(t_global *gl, char *roomNameToCheck);
int		check_valid_link(t_global *gl, char **words);
int		add_link_to_dict(t_global *gl, int fd, char *line);
void	check_read_link_info_results(t_global *gl, int fd);
void	read_link_info(t_global *gl, int fd, char *line);

/*
**	Paths finding functions
*/

/*
**	Ants dispactch functions
*/

/*
**	Diverse functions
*/

void	free_rooms(t_room *rooms);
void	free_entree(t_entree *ent);
void	free_dict(t_dict *dict);
void	free_paths(t_path *paths);
void	free_global(t_global *gl);

void	free_words(char **words);

void	print_global(t_global *gl);

char	*ft_strtrim_free(char *str);

#endif
