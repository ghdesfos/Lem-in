/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_ants_through_paths.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:17:48 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 18:13:25 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/*
**	We move the ants forward along their path (first while loop).
**	If the first ant (most advanced ant) has reached the end, \
**	we remove it (second while loop).
*/

void	move_ants_forward(t_global *gl, t_dispatch **disTab)
{
	t_path		*path;
	t_dispatch	*tmp;
	int			i;

	i = 0;
	path = gl->paths;
	while (path)
	{
		tmp = disTab[i];
		if (tmp)
		{
			while (tmp)
			{
				tmp->room = tmp->room->next;
				tmp = tmp->next;
			}
			tmp = disTab[i];
			if (NULL == tmp->room)
			{
				disTab[i] = tmp->next;
				free(tmp);
			}
		}
		i++;
		path = path->next;
	}
}

/*
**	We try to add one more ant on each path.
**	Yet we don't do it if we have already sent enough ants on this path.
*/

void	dispatch_new_ants_batch(t_global *gl, int *dispatchedAnts, \
									t_dispatch **disTab)
{
	t_path		*path;
	t_dispatch	*tmp;
	int			i;

	i = 0;
	path = gl->paths;
	while (path)
	{
		if (path->dispatchedAnts < path->antsToDispatch)
		{
			path->dispatchedAnts += 1;
			*dispatchedAnts += 1;
			tmp = disTab[i];
			if (!tmp)
				disTab[i] = create_dispatch_elem(*dispatchedAnts, path);
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = create_dispatch_elem(*dispatchedAnts, path);
			}
		}
		i++;
		path = path->next;
	}
}

void	print_ants_movement(t_global *gl, t_dispatch **disTab)
{
	t_dispatch	*disp;
	int			i;
	int			flag;

	flag = 1;
	i = -1;
	while (++i < gl->nbPaths)
	{
		disp = disTab[i];
		while (disp)
		{
			if (flag)
				b_printf("%c%d-%s", SOLUTION_CHAR, disp->antNb, disp->room->name);
			else
				b_printf(" %c%d-%s", SOLUTION_CHAR, disp->antNb, disp->room->name);
			flag = 0;
			disp = disp->next;
		}
	}
	b_printf("\n");
}

/*
**	We first share ants through all paths up to the moment where their length \
**	and their ants number reached gl->maxPathLen.
**	Then we dispatch the remaining ants between each path equally.
*/

void	define_ants_number_for_each_path(t_global *gl)
{
	t_path	*path;
	int		dispatchedAnts;

	dispatchedAnts = 0;
	path = gl->paths;
	while (path)
	{
		path->antsToDispatch = gl->maxPathLen - path->len;
		dispatchedAnts += path->antsToDispatch;
		path = path->next;
	}
	path = gl->paths;
	while (dispatchedAnts < gl->nbAnts)
	{
		if (NULL == path)
			path = gl->paths;
		path->antsToDispatch += 1;
		dispatchedAnts += 1;
		path = path->next;
	}
}

void	dispatch_ants_through_paths(t_global *gl)
{
	t_path		*path;
	t_dispatch	*disTab[gl->nbPaths];
	int			dispatchedAnts;
	int			i;	

	define_ants_number_for_each_path(gl);
	i = -1;
	while (++i < gl->nbPaths)
		disTab[i] = NULL;
	path = gl->paths;
	dispatchedAnts = 0;
	while (1)
	{
		move_ants_forward(gl, disTab);
		dispatch_new_ants_batch(gl, &dispatchedAnts, disTab);
		if (check_all_ants_have_reached_end(gl, dispatchedAnts, disTab))
			return ;
		print_ants_movement(gl, disTab);
	}
}
