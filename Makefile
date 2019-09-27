# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 17:57:10 by ghdesfos          #+#    #+#              #
#    Updated: 2019/09/26 11:49:07 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= /bin/rm -rf
LIBFT		= libft/libft.a
LIBFTPRINTF	= b_printf/libftprintf.a
LIB			= -L libft/ -lft\
				-L b_printf/ -lftprintf
INCLUDES	= -I includes\
				-I libft\
				-I srcs/get_next_line\
				-I b_printf

MAIN		= lem-in.c
DICTIONARY	= dictionary.c\
				dictionary_sub.c
READ_INPUT	= read_input.c\
				read_ants_number.c\
				read_room_info.c\
				read_room_info_error_management.c\
				read_link_info.c
DIVERSE		= basic_check_functions.c\
				the_free_functions.c\
				the_free_functions_2.c\
				print_functions.c\
				useful_functions.c
GET_NEXT_L	= get_next_line/get_next_line.c

FUNCTIONS	= $(MAIN) $(DICTIONARY) $(READ_INPUT) $(DIVERSE) $(GET_NEXT_L) $(B_PRINTF)
FILES		= $(addprefix srcs/, $(FUNCTIONS))
OBJECTS		= $(FILES:.o=.c)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C b_printf

$(NAME): $(LIBFT) $(LIBFTPRINTF) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB)

g: $(LIBFT) $(LIBFTPRINTF) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB) -g

gg: $(LIBFT) $(LIBFTPRINTF) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LIB) -g -fsanitize=address

val:
	valgrind --leak-check=full -v ./lem-in

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

.PHONY: all clean fclean re
