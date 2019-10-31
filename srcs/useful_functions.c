/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:45:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 16:29:30 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

char	*ft_strtrim_free(char *str)
{
	char *newStr;

	if (!str)
		return (NULL);
	newStr = ft_strtrim(str);
	free(str);
	return (newStr);
}

/*
**	We use this function to store the lines from the input file.
**	We store the lines in the reverse order.
*/

int		add_line_to_struct(t_global *gl, char *lineStr)
{
	t_line *lineNode;

	if (!(lineNode = (t_line*)malloc(sizeof(t_line))))
		return (-1);
	lineNode->line = ft_strdup(lineStr);
	lineNode->next = gl->lines;
	gl->lines = lineNode;
	return (1);
}

/*
**	With the below function we print the lines (corresponding to the content \
**	of the input file) contained inside the struct s_line list.
**	We print them in the reverse order friom the list as they are saved in \
**	reverse order in the list.
*/

void	print_input_file_lines(t_line *lines)
{
	if (!lines)
		return ;
	print_input_file_lines(lines->next);
	b_printf("%s\n", lines->line);
}
