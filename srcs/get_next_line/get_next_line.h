/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 19:52:29 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/25 19:52:36 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFF_SIZE 4

typedef struct		s_file
{
	char			*content;
	int				fd;
	struct s_file	*next;
}					t_file;

int					get_next_line(const int fd, char **line);

#endif
