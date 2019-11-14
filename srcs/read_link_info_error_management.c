/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_link_info_error_management.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:17:16 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/13 13:25:03 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	read_link_info_error_management(t_global *gl, char **words, \
											char *line, int flag)
{
	if (0 == flag)
	{
		ft_putstr_fd("ERROR\nsome links are invalid\n", STDERR_FILENO);
		free_global(gl);
		free_words(words);
		free(line);
		exit(-4);
	}
	else if (1 == flag)
	{
		ft_putstr_fd("ERROR\nproblem with the adding of some links \
to the dictionary\n", STDERR_FILENO);
		free_global(gl);
		free_words(words);
		free(line);
		exit(-4);
	}
}
