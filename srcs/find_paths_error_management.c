/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths_error_management.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:16:26 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 17:51:01 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	find_paths_error_management(t_global *gl)
{
	if (NULL == gl->paths)
	{
		ft_putstr_fd("ERROR\nthere is no path linking the start \
and end rooms\n", 2);
		free_global(gl);
		exit(-6);
	}
}
