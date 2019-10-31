/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:57:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 19:53:50 by ghdesfos         ###   ########.fr       */
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
**	@param {nbAnts} is the number of ants to bring from the start to the end point.
**	@param {start} contains the name of the room where the ants start.
**	@param {end} contains the name of the roo, where the ants finish.
**	@param {rooms} is the list of rooms that constitute the graph.
**	@param {dict} contains for each room the list of rooms that are linked to it, \
**	in other words it contains the edge information of the graph.
**	@param {paths} contains the list of paths we will use to dispatch the ants from \
**	the start to the end the most rapidly possible.
*/

typedef					struct s_global
{
	int					nbAnts;
	struct s_line		*lines;
	int					nbRooms;
	char				*start;
	char				*end;
	struct s_room		*rooms;
	struct s_dict		*dict;
	struct s_path		*paths;
	int					nbPaths;
	int					minPathLen;
	int					maxPathLen;
}						t_global;

/*
**	This struct will contain the lines from the file read.
**	We will print these lines and thus the input text if there was no error \
**	in the input.
*/

typedef					struct s_line
{
	char				*line;
	struct s_line		*next;
}						t_line;

/*
**	This struct contains the name of the rooms in the graph.
**	This list helps doing some error management.
**	This struct is also used inside the path structure.
*/

typedef					struct s_room
{
	char				*name;
	int					x;
	int					y;
	struct s_room		*next;
}						t_room;

/*
**	This dict contains the link information between the rooms (edges of the graph).
**	@param {size} is the number of the dictionary.
**	@param {entrees} will contain the different dictionary entree lists.
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
	int					x;
	int					y;
	int					nbValues;
	t_entree			**values;
	int					vertexNb;
}						t_keyvalue;

/*
**	Node structure used for the queue and the stack
*/

typedef					struct s_node
{
	void				*content;
	struct s_node		*next;
}						t_node;

typedef					struct s_pathelem
{
	struct s_entree		*curr;
	struct s_entree		*prev;
}						t_pathelem;

/*
**	Queue structure
*/

typedef				struct s_queue
{
	struct s_node	*first;
	struct s_node	*last;
}					t_queue;

/*
**	Stack structure
*/

typedef				struct s_stack
{
	struct s_node	*top;
}					t_stack;

/*
**	Path structure to store the different pathes found
*/

typedef					struct s_path
{
	struct s_room		*rooms;
	int					len;
	int					antsToDispatch;
	int					dispatchedAnts;
	struct s_path		*next;
}						t_path;

/*
**	Dispatch structure to store the position of an ant inside a path.
**	Hence each dispatch node corresponds to the movement of an ant \
**	through the graph.
*/

typedef					struct s_dispatch
{
	int					antNb;
	t_room				*room;
	struct s_dispatch	*next;
}						t_dispatch;

# define SIZE_DICT		1000

# define COMMENT_CHAR	'#'
# define SOLUTION_CHAR	'L'
# define STR_START		"##start"
# define STR_END		"##end"

# define NORMAL_ROOM	0
# define START_ROOM		1
# define END_ROOM		2

# define START_ROOM_ERR	1
# define END_ROOM_ERR	2
# define ST_AND_END_ERR	3

# define ENT_DATA		((t_keyvalue*)(ent->data))
# define ENT_CH_DATA(i)	((t_keyvalue*)(((t_keyvalue*)(ent->data))->values[i]->data))
# define ENT_NB(i)		(&((dict->entrees)[i]))

# define FD				0

/*
**	Initialization functions
*/

int		init_gl(t_global *gl);

/*
**	Input reading functions
*/

int		check_contains_just_digits(char *line);
int		check_is_a_positive_int(char *line);

void	read_input(t_global *gl);

void	read_ants_number_error_management(t_global *gl, int fd);
void	read_ants_number(t_global *gl, int fd);

int		add_room_to_rooms_list(t_global *gl, char **words);
int		add_room_to_dict(t_global *gl, char *line, int roomType);
void	start_line_flag_management(t_global *gl, int fd, char *line, \
									int *flagStart);
void	end_line_flag_management(t_global *gl, int fd, char *line, \
									int *flagEnd);
void	read_room_info(t_global *gl, int fd, char **line, int *flags);

int		check_valid_room(char **words);
void	read_room_info_error_management(t_global *gl, int fd, char *line, \
											int errorNb);
int		check_all_rooms_have_different_names(t_global *gl);
int		check_all_rooms_have_different_coordinates(t_global *gl);
void	check_read_room_info_results(t_global *gl, int fd, char *line);

int		check_existing_room_name(t_global *gl, char *roomNameToCheck);
int		check_valid_link(t_global *gl, char **words);
int		add_link_to_dict(t_global *gl, int fd, char *line);
void	check_read_link_info_results(t_global *gl, int fd);
void	read_link_info(t_global *gl, int fd, char *line);

/*
**	Dictionary functions
*/

t_entree	*dict_insert(t_dict *dict, char *key, char *value);
t_entree	*dict_search(t_dict *dict, char *key);
t_dict		*dict_init(int capacity);

size_t		hash(unsigned char *input);
int			add_value_to_entree(t_entree *ent, t_entree *valueNode);
t_entree	*create_new_entree(t_entree **entrees, char *key);
t_entree	*find_entree(t_dict *dict, char *key);

/*
**	Queue functions
*/

struct s_queue	*init_queue(void);
void			enqueue(struct s_queue *queue, void *content);
void			*dequeue(struct s_queue *queue);
void			*peek_queue(struct s_queue *queue);
int				is_empty_queue(struct s_queue *queue);

/*
**	Stack functions
*/

struct s_stack	*init_stack(void);
void			*pop_stack(struct s_stack *stack);
void			push_stack(struct s_stack *stack, void *content);
void			*peek_stack(struct s_stack *stack);
int				is_empty_stack(struct s_stack *stack);

/*
**	Paths finding functions
*/

void	add_non_visited_neighbors(t_entree *ent, t_queue *queue, \
									int *newVisited);
t_room	*add_room_elem_to_path(t_path *path, t_pathelem *pathElem);
t_path	*reconstitute_path(t_stack *stack, t_entree *start);
t_path	*find_specific_path(t_global *gl, int *visited, t_entree *start, \
							t_entree *end);
void	find_paths(t_global *gl);

t_path		*create_path_elem(void);
t_pathelem	*create_pathelem_elem(t_entree *curr, t_entree *prev);
void	find_paths_error_management(t_global *gl);
void	mark_new_path_rooms_as_visited(t_global *gl, t_path *newPath, \
									int *visited);
int		check_new_path_fastens_dispatch(t_global *gl, t_path *newPath);

void	free_non_empty_stack(t_stack *stack);

/*
**	Ants dispactch functions
*/

void	move_ants_forward(t_global *gl, t_dispatch **disTab);
void	dispatch_new_ants_batch(t_global *gl, int *dispatchedAnts, \
									t_dispatch **disTab);
void	print_ants_movement(t_global *gl, t_dispatch **disTab);
void	define_ants_number_for_each_path(t_global *gl);
void	dispatch_ants_through_paths(t_global *gl);

t_dispatch	*create_dispatch_elem(int antNb, t_path *path);
int		check_all_ants_have_reached_end(t_global *gl, int dispatchedAnts, \
											t_dispatch **disTab);

/*
**	Diverse functions
*/

void	free_rooms(t_room *rooms);
void	free_entree(t_entree *ent);
void	free_dict(t_dict *dict);
void	free_paths(t_path *paths);
void	free_global(t_global *gl);

void	free_words(char **words);
void	free_lines(t_line *lines);

void	print_global(t_global *gl);

char	*ft_strtrim_free(char *str);
int		add_line_to_struct(t_global *gl, char *lineStr);
void	print_input_file_lines(t_line *lines);

#endif
