# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 17:57:10 by ghdesfos          #+#    #+#              #
#    Updated: 2019/11/12 21:37:36 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -lncurses
RM			= /bin/rm -rf
LIBFT		= libft/libft.a
LIBFTPRINTF	= b_printf/libftprintf.a
LIB			= -L libft/ -lft\
				-L b_printf/ -lftprintf
INCLUDES	= -I includes\
				-I libft\
				-I srcs/get_next_line\
				-I b_printf
HEADERS		= includes/lem_in.h

MAIN		= lem_in.c
DICTIONARY	= dictionary.c\
				dictionary_sub.c
QUEUE		= queue.c
STACK		= stack.c
READ_INPUT	= read_input.c\
				read_ants_number.c\
				read_room_info.c\
				read_room_info_error_management.c\
				read_link_info.c\
				read_link_info_error_management.c
FIND_PATH	= find_paths.c\
				find_paths_sub.c\
				find_paths_error_management.c
DISPATCH	= dispatch_ants_through_paths.c\
				dispatch_ants_through_paths_sub.c
VISUALIZER	= visualizer.c\
				visualizer_map_creation.c\
				visualizer_map_creation_sub.c\
				visualizer_setup_functions.c\
				visualizer_check_functions.c\
				visualizer_print_functions.c\
				visualizer_utilities.c
DIVERSE		= basic_check_functions.c\
				the_free_functions.c\
				the_free_functions_2.c\
				the_free_functions_3.c\
				print_functions.c\
				useful_functions.c
GET_NEXT_L	= get_next_line/get_next_line.c

FUNCTIONS	= $(MAIN) $(DICTIONARY) $(QUEUE) $(STACK) $(READ_INPUT) $(FIND_PATH) $(DISPATCH) $(VISUALIZER) $(DIVERSE) $(GET_NEXT_L)
FILES		= $(addprefix srcs/, $(FUNCTIONS))
OBJECTS		= $(FILES:.o=.c)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C b_printf

$(NAME): $(LIBFT) $(LIBFTPRINTF) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB)

g: $(LIBFT) $(LIBFTPRINTF) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB) -g

gg: $(LIBFT) $(LIBFTPRINTF) $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB) -g -fsanitize=address

val:
	valgrind --leak-check=full -v ./$(NAME)

clean:
	make clean -C libft
	make clean -C b_printf
	$(RM) $(OBJS)
	$(RM) *.gch
	$(RM) *.dSYM

fclean: clean
	make fclean -C libft
	make fclean -C b_printf
	$(RM) $(NAME)

re: fclean all
	make re -C libft
	make re -C b_printf

.PHONY: all clean fclean re g gg val
