/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 11:57:46 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/11 22:59:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <ncurses.h>
# include "libft.h"
# include "get_next_line.h"
# include "b_printf.h"

/*
**	@param {nbAnts} is the number of ants to bring from the start to \
**	the end point.
**	@param {lines} contains the lines from the input file, to be printed \
**	if there is no error in the input.
**	@param {start} contains the name of the room where the ants start.
**	@param {end} contains the name of the room where the ants finish.
**	@param {rooms} is the list of rooms that constitute the graph.
**	@param {dict} contains for each room the list of rooms that are linked \
**	to it, in other words it contains the edge information of the graph.
**	@param {nb_paths} contains the number of paths we accepyt for the dispatch.
**	@param {paths} contains the list of paths we will use to dispatch \
**	the ants from the start to the end the most rapidly possible.
**	@param {max_path_len} is used to determine if we accept a new path or not.
**	@param {dispatch_moves} is the total number of moves to bring all ants \
**	from start to end.
**	@param {maxRoomCoorX} contains the max x coordinates of all rooms.
**	@param {maxRoomCoorY} contains the max y coordinates of all rooms.
**	@param {map} contains the map to print for the visualizer.
*/

typedef	struct			s_global
{
	unsigned char		options;
	int					nb_ants;
	struct s_line		*lines;
	int					nb_rooms;
	char				*start;
	char				*end;
	struct s_room		*rooms;
	struct s_dict		*dict;
	int					nb_paths;
	struct s_path		*paths;
	int					max_path_len;
	int					dispatch_moves;
	int					max_room_coor_x;
	int					max_room_coor_y;
	struct s_map_elem	**map;
}						t_global;

/*
**	This struct will contain the lines from the file read.
**	We will print these lines and thus the input text if there was no error \
**	in the input.
*/

typedef struct			s_line
{
	char				*line;
	struct s_line		*next;
}						t_line;

/*
**	This struct contains the name of the rooms in the graph.
**	This list helps doing some error management.
**	This struct is also used inside the path structure.
*/

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	struct s_room		*next;
}						t_room;

/*
**	This dict contains the link information between \
**	the rooms (edges of the graph).
**
**	@param {size} is the number of the dictionary.
**	@param {entrees} will contain the different dictionary entree lists.
*/

typedef struct			s_dict
{
	int					size;
	struct s_entree		**entrees;
}						t_dict;

typedef struct			s_entree
{
	void				*data;
	struct s_entree		*next;
}						t_entree;

/*
**	struct to be used as the data of the struct s_entree.
**
**	@param {key} corresponds to the room name.
**	@param {nb_values} correspond to the number of rooms connected \
**	to this room.
**	@param {values} contains the addresses of the struct s_entree that \
**	correspond to the rooms connected to this room.
**	@param {vertex_nb} correspond to the specific number of this vertex \
**	(by creation order).
*/

typedef struct			s_keyvalue
{
	char				*key;
	int					x;
	int					y;
	int					nb_values;
	t_entree			**values;
	int					vertex_nb;
}						t_keyvalue;

/*
**	Node structure used for the queue and the stack
*/

typedef struct			s_node
{
	void				*content;
	struct s_node		*next;
}						t_node;

/*
**	Structure used to find new pathes.
**	It represents the link between 2 vertices.
*/

typedef struct			s_pathelem
{
	struct s_entree		*curr;
	struct s_entree		*prev;
}						t_pathelem;

/*
**	Queue structure
*/

typedef struct			s_queue
{
	struct s_node		*first;
	struct s_node		*last;
}						t_queue;

/*
**	Stack structure
*/

typedef struct			s_stack
{
	struct s_node		*top;
}						t_stack;

/*
**	Path structure to store the different pathes found
**
**	@param {rooms} contains the rooms in this path.
**	@param {len} corresponds to the length of the path.
**	@param {ants_to_dispatch} corresponds to the number of ants \
**	to send on this path.
**	@param {dispatched_ants} corresponds to the number of ants already \
**	sent on this path.
*/

typedef struct			s_path
{
	struct s_room		*rooms;
	int					len;
	int					ants_to_dispatch;
	int					dispatched_ants;
	struct s_path		*next;
}						t_path;

/*
**	Dispatch structure to store the position of an ant inside a path.
**	Hence each dispatch node corresponds to the movement of an ant \
**	through the graph.
**
**	@param {ant_nb} is the specific identifier of this ant.
**	@param {room} points to the room where this ant currently is.
**	@param {prev_room} used for the visualizer to have the ant moved \
**	from the previous room to the current one.
**	@param {coor} used for the visualizer to describe the ant \
**	movement from the previous room to the current one.
**	@param {delay} is used for the dispatch of the ant to send them \
**	one by one on each path.
*/

typedef struct			s_dispatch
{
	int					ant_nb;
	t_room				*room;
	int					coor[2];
	int					delay;
	struct s_dispatch	*next;
}						t_dispatch;

/*
**	This struct is used for the visualizer.
**	It contains the information of the rooms and pathes to be printed.
**
**	@param {pchar} corresponds to the char to be printed.
**	@param {flag_path} corresponds to the flag to know if the room or \
**	path element is used during the dispatch.
*/

typedef struct			s_map_elem
{
	char				pchar;
	int					flag_path;
}						t_map_elem;

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
# define ENT_CH_DATA(i)	((t_keyvalue*)(ENT_DATA->values[i]->data))
# define ENT_NB(i)		(&((dict->entrees)[i]))

# define FD				0

# define CHAR_SOURCE	'S'
# define CHAR_SINK		'T'
# define CHAR_ROOM		'R'
# define CHAR_HORIZ		'-'
# define CHAR_VERTI		'|'
# define CHAR_INTERSECT	'+'
# define CHAR_ANT		'@'

/*
**	Time needed for an ant to make one step forward in microseconds.
*/

# define ANT_SPEED		50000

/*
**	Below we used the macros defined in the <ncurses.h> header.
*/

# define BLUE			COLOR_CYAN
# define GREEN			COLOR_GREEN
# define YELLOW			COLOR_YELLOW
# define RED			COLOR_RED
# define WHITE			COLOR_WHITE
# define BLACK			COLOR_BLACK

# define C_PAIR_BLUE	1
# define C_PAIR_GREEN	2
# define C_PAIR_YELLOW	3
# define C_PAIR_RED		4
# define C_PAIR_WHITE	5

/*
**	Flag n prints the number of moves to bring all ants from start to end.
**	Flag p prints the pathes that are used for the dispatch.
**	Flag q makes the program run in quiet mode, only the ants moves \
**	are printed.
**	Flag v launches the visualizer.
*/

# define FLAGS			"npqv"
# define FLAG_N			1
# define FLAG_P			2
# define FLAG_Q			4
# define FLAG_V			4
# define USAGE			"Usage: ./lem-in -[npqv] < input_file\n"

/*
**	Initialization functions
*/

int						init_gl(t_global *gl);

/*
**	Input reading functions
*/

int						check_contains_just_digits(char *line);
int						check_is_a_positive_int(char *line);

void					read_input(t_global *gl);

void					read_ants_number_error_management(t_global *gl, int fd);
void					read_ants_number(t_global *gl, int fd);

int						add_room_to_rooms_list(t_global *gl, char **words);
int						add_room_to_dict(t_global *gl, char *line, \
											int room_type);
void					start_line_flag_management(t_global *gl, int fd, \
													char *line, \
													int *flag_start);
void					end_line_flag_management(t_global *gl, int fd, \
													char *line, int *flag_end);
void					read_room_info(t_global *gl, int fd, char **line, \
										int *flags);

int						check_valid_room(char **words);
void					read_room_info_error_management(t_global *gl, int fd, \
															char *line, \
															int error_nb);
int						check_all_rooms_have_different_names(t_global *gl);
int						check_all_rooms_have_different_coordinates(t_global \
																	*gl);
void					check_read_room_info_results(t_global *gl, int fd, \
														char *line);

int						check_existing_room_name(t_global *gl, \
													char *room_name_to_check);
int						check_valid_link(t_global *gl, char **words);
int						add_link_to_dict(t_global *gl, int fd, char *line);
void					read_link_info(t_global *gl, int fd, char *line);

void					read_link_info_error_management(t_global *gl, \
															char **words, \
															char *line, \
															int flag);
/*
**	Dictionary functions
*/

t_entree				*dict_insert(t_dict *dict, char *key, char *value);
t_entree				*dict_search(t_dict *dict, char *key);
t_dict					*dict_init(int capacity);

size_t					hash(unsigned char *input);
int						add_value_to_entree(t_entree *ent, \
												t_entree *value_node);
t_entree				*create_new_entree(t_entree **entrees, char *key);
t_entree				*find_entree(t_dict *dict, char *key);

/*
**	Queue functions
*/

struct s_queue			*init_queue(void);
void					enqueue(struct s_queue *queue, void *content);
void					*dequeue(struct s_queue *queue);
void					*peek_queue(struct s_queue *queue);
int						is_empty_queue(struct s_queue *queue);

/*
**	Stack functions
*/

struct s_stack			*init_stack(void);
void					*pop_stack(struct s_stack *stack);
void					push_stack(struct s_stack *stack, void *content);
void					*peek_stack(struct s_stack *stack);
int						is_empty_stack(struct s_stack *stack);

/*
**	Paths finding functions
*/

void					add_non_visited_neighbors(t_entree *ent, \
													t_queue *queue, \
													int *new_visited);
t_room					*add_room_elem_to_path(t_path *path, \
												t_pathelem *path_elem);
t_path					*reconstitute_path(t_stack *stack, t_entree *start);
t_path					*find_specific_path(t_global *gl, int *visited, \
												t_entree *start, \
							t_entree *end);
void					find_paths(t_global *gl);

t_path					*create_path_node(void);
t_pathelem				*create_pathelem_node(t_entree *curr, t_entree *prev);
void					add_new_path_to_paths_list(t_global *gl, \
													t_path *new_path);
void					mark_new_path_rooms_as_visited(t_global *gl, \
														t_path *new_path, \
									int *visited);
int						check_new_path_fastens_dispatch(t_global *gl, \
															t_path *new_path);

void					find_paths_error_management(t_global *gl);

/*
**	Ants dispactch functions
*/

void					move_ants_forward(t_global *gl, t_dispatch **dis_tab, \
											int i);
void					dispatch_new_ants_batch(t_global *gl, \
													int *dispatched_ants, \
													t_dispatch **dis_tab);
void					print_ants_movement(t_global *gl, t_dispatch **dis_tab);
void					define_ants_number_for_each_path(t_global *gl);
void					dispatch_ants_through_paths(t_global *gl);

t_dispatch				*create_dispatch_elem(int ant_nb, t_path *path, \
												int *coor, int delay);
int						check_all_ants_have_reached_end(t_global *gl, \
														int dispatched_ants, \
														t_dispatch **dis_tab);

/*
**	Visualizer functions
*/

void					create_visualizer_map_error_management(t_global *gl);
void					create_visualizer_map(t_global *gl);

void					add_rooms_to_visualizer_map(t_global *gl);
void					add_link_elements_to_visualizer_map(t_global *gl, \
											int *coor1, int *coor2);
void					add_link_to_visualizer_map(t_global *gl, char **words);
void					apply_specific_path_to_visualizer_map(t_global *gl, \
																t_room *room);
void					apply_paths_to_visualizer_map(t_global *gl);

void					move_ants_to_next_room_in_visualizer_sub(\
															t_dispatch *tmp, \
															int *change_flag);
void					move_ants_to_next_room_in_visualizer(t_global *gl, \
															t_dispatch **ants, \
															int move_nb);
void					update_ants_next_room_in_visualizer(t_global *gl, \
															t_dispatch **ants, \
															int move_nb);
void					launch_visualizer(t_global *gl);

void					visualizer_color_error_management(t_global *gl);
void					set_up_or_end_ncurses_environment(t_global *gl, \
															int flag);
void					set_up_ants_for_visualizer(t_global *gl, \
													t_dispatch **ants);

void					check_window_size_for_visualizer(t_global *gl);
int						check_all_ants_have_reached_end_visualizer(\
														t_global *gl, \
														t_dispatch **ants);

void					print_char_in_color(char c, int color_pair, int bold);
void					print_visualizer_map(t_global *gl);
void					print_ants_in_visualizer(t_global *gl, \
													t_dispatch **ants, \
													int move_nb);

void					update_max_room_coordinates(t_global *gl, \
														t_entree *ent);
void					swap_coordinates(int *coor1, int *coor2);

/*
**	Diverse functions
*/

void					free_rooms(t_room *rooms);
void					free_entrees(t_entree *ent);
void					free_dict(t_dict *dict);
void					free_paths(t_path *paths);
void					free_global(t_global *gl);

void					free_words(char **words);
void					free_lines(t_line *lines);
void					free_dispatchs(t_dispatch **dispatchs, int size, \
										int flag);
void					free_non_empty_stack(t_stack *stack);
void					free_non_empty_queue(t_queue *queue);

void					free_visualizer_map(t_global *gl, t_map_elem **map);

void					print_rooms(t_room *rooms);
void					print_entrees(t_entree **entrees);
void					print_dict(t_dict *dict);
void					print_paths(t_path *paths);
void					print_global(t_global *gl);

char					*ft_strtrim_free(char *str);
int						add_line_to_struct(t_global *gl, char *line_str);
void					print_input_file_lines_rec(t_line *lines);
void					print_input_file_lines(t_line *lines);
void					print_total_moves(t_global *gl);

#endif
