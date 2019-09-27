/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 09:44:45 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/26 17:06:24 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_rooms(t_room *rooms)
{
	t_room *tmp;

	tmp = rooms;
	b_printf("PRINTING OF THE ROOMS:\n");
	while (tmp)
	{
		b_printf("Room name %s, x %d, y %d\n", tmp->name, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	b_printf("\n");
}

void	print_words(char **words)
{
	int i;

	if (!words)
		return ;
	i = -1;
	while (words[++i])
		b_printf("word: %s, ", words[i]);
	b_printf(" ; ");
}

void	print_entrees(t_entree **entrees)
{
	t_entree *ent;

	if (!entrees)
		return ;
	ent = *entrees;
	while (ent)
	{
		b_printf("Key %s --> ", ENT_DATA->key);
		print_words(ENT_DATA->values);
		ent = ent->next;
	}
	b_printf("\n");
}

void	print_dict(t_dict *dict)
{
	int i;

	if (!dict)
		return ;
	b_printf("PRINTING OF THE DICT\n");
	b_printf("Dict size: %d\n", dict->size);
	i = -1;
	while (++i < dict->size)
	{
		if ((dict->entrees)[i])
		{
			b_printf("Dict rk: %d:\n", i);
			print_entrees(ENT_NB(i));
		}
	}
}

void	print_global(t_global *gl)
{
	b_printf("Start room %s\n", gl->start);
	b_printf("End room %s\n", gl->end);

	printf("TEST 1234\n");
	print_rooms(gl->rooms);
	printf("TEST 5678\n");
	print_dict(gl->dict);
}
