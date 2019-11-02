/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_ants_through_paths.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 18:17:48 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/11/01 18:41:41 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	We move the ants forward along their path (first while loop).
**	If the first ant (most advanced ant) has reached the end, \
**	we remove it (second if statement).
*/

void	move_ants_forward(t_global *gl, t_dispatch **dis_tab, int i)
{
	t_path		*path;
	t_dispatch	*tmp;

	i = 0;
	path = gl->paths;
	while (path)
	{
		tmp = dis_tab[i];
		if (tmp)
		{
			while (tmp)
			{
				tmp->room = tmp->room->next;
				tmp = tmp->next;
			}
			tmp = dis_tab[i];
			if (NULL == tmp->room)
			{
				dis_tab[i] = tmp->next;
				free(tmp);
			}
		}
		i++;
		path = path->next;
	}
}

/*
**	We try to add one more ant on each path.
**	Yet we don't do it if we have already sent enough ants onto this path.
*/

void	dispatch_new_ants_batch(t_global *gl, int *dispatched_ants, \
									t_dispatch **dis_tab)
{
	t_path		*path;
	t_dispatch	*tmp;
	int			i;

	i = 0;
	path = gl->paths;
	while (path)
	{
		if (path->dispatched_ants < path->ants_to_dispatch)
		{
			path->dispatched_ants += 1;
			*dispatched_ants += 1;
			tmp = dis_tab[i];
			if (!tmp)
				dis_tab[i] = create_dispatch_elem(*dispatched_ants, path);
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = create_dispatch_elem(*dispatched_ants, path);
			}
		}
		i++;
		path = path->next;
	}
}

void	print_ants_movement(t_global *gl, t_dispatch **dis_tab)
{
	t_dispatch	*disp;
	int			i;
	int			flag;

	flag = 1;
	i = -1;
	while (++i < gl->nb_paths)
	{
		disp = dis_tab[i];
		while (disp)
		{
			if (flag)
				b_printf("%c%d-%s", SOLUTION_CHAR, disp->ant_nb, \
													disp->room->name);
			else
				b_printf(" %c%d-%s", SOLUTION_CHAR, disp->ant_nb, \
													disp->room->name);
			flag = 0;
			disp = disp->next;
		}
	}
	b_printf("\n");
}

/*
**	We first share ants through all paths up to the moment where their length \
**	+ their ants number reached gl->max_path_len.
**	Then we dispatch the remaining ants between each path equally.
*/

void	define_ants_number_for_each_path(t_global *gl)
{
	t_path	*path;
	int		dispatched_ants;

	dispatched_ants = 0;
	path = gl->paths;
	while (path)
	{
		path->ants_to_dispatch = gl->max_path_len - path->len;
		dispatched_ants += path->ants_to_dispatch;
		path = path->next;
	}
	path = gl->paths;
	while (dispatched_ants < gl->nb_ants)
	{
		if (NULL == path)
			path = gl->paths;
		path->ants_to_dispatch += 1;
		dispatched_ants += 1;
		path = path->next;
	}
}

void	dispatch_ants_through_paths(t_global *gl)
{
	t_path		*path;
	t_dispatch	*dis_tab[gl->nb_paths];
	int			dispatched_ants;
	int			i;

	define_ants_number_for_each_path(gl);
	i = -1;
	while (++i < gl->nb_paths)
		dis_tab[i] = NULL;
	path = gl->paths;
	dispatched_ants = 0;
	while (1)
	{
		move_ants_forward(gl, dis_tab, 0);
		dispatch_new_ants_batch(gl, &dispatched_ants, dis_tab);
		if (check_all_ants_have_reached_end(gl, dispatched_ants, dis_tab))
			return ;
		print_ants_movement(gl, dis_tab);
	}
}
