/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 13:45:25 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:29:40 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_strtrim_free(char *str)
{
	char *new_str;

	if (!str)
		return (NULL);
	new_str = ft_strtrim(str);
	free(str);
	return (new_str);
}

/*
**	We use this function to store the lines from the input file.
**	We store the lines in the reverse order.
*/

int		add_line_to_struct(t_global *gl, char *line_str)
{
	t_line *line_node;

	if (!(line_node = (t_line*)malloc(sizeof(t_line))))
		return (-1);
	line_node->line = ft_strdup(line_str);
	line_node->next = gl->lines;
	gl->lines = line_node;
	return (1);
}

/*
**	With the below function we print the lines (corresponding to the content \
**	of the input file) contained inside the struct s_line list.
**	We print them in the reverse order from the list as they are saved in \
**	reverse order in the list.
*/

void	print_input_file_lines_rec(t_line *lines)
{
	if (!lines)
		return ;
	print_input_file_lines_rec(lines->next);
	b_printf("%s\n", lines->line);
}

void	print_input_file_lines(t_line *lines)
{
	if (!lines)
		return ;
	print_input_file_lines_rec(lines);
	b_printf("\n");
}

void	print_total_moves(t_global *gl)
{
	b_printf("\nTotal number of moves to bring the %d ants to the sink: %d\n", \
				gl->nb_ants, gl->dispatch_moves);
}
