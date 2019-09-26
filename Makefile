# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/25 17:57:10 by ghdesfos          #+#    #+#              #
#    Updated: 2019/09/25 18:08:05 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= /bin/rm -rf

SRCS		= 
OBJS		= $(SRCS:.o=.c)
INCS		= 

all: $(NAME)

$(NAME): $(OBJS)

g: $(NAME)

gg: $(NAME)

val:

clean:
	$(RM) $(OBJS)
	$(RM) *.gch
	$(RM) *.dSYM

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
