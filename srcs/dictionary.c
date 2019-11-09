/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:58:31 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 18:06:11 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_entree	*dict_insert(t_dict *dict, char *key, char *value)
{
	int			rk;
	t_entree	*ent;
	t_entree	*value_node;

	if (!dict || !key)
		return (NULL);
	if (NULL == (ent = find_entree(dict, key)))
	{
		rk = (unsigned int)hash((unsigned char*)key) % dict->size;
		if (NULL == (ent = create_new_entree(ENT_NB(rk), key)))
			return (NULL);
	}
	if (value)
	{
		if (NULL == (value_node = dict_search(dict, value)))
			return (NULL);
		if (-1 == add_value_to_entree(ent, value_node))
			return (NULL);
	}
	return (ent);
}

t_entree	*dict_search(t_dict *dict, char *key)
{
	t_entree	*ent;

	if (!dict || !key)
		return (NULL);
	if (NULL == (ent = find_entree(dict, key)))
		return (NULL);
	return (ent);
}

t_dict		*dict_init(int capacity)
{
	t_dict	*dict;
	int		i;

	if (capacity < 1)
		return (NULL);
	if (!(dict = (t_dict*)malloc(sizeof(t_dict))))
		return (NULL);
	dict->size = capacity;
	if (!(dict->entrees = (t_entree**)malloc(sizeof(t_entree*) \
												* (capacity + 1))))
		return (NULL);
	i = -1;
	while (++i < capacity + 1)
		(dict->entrees)[i] = NULL;
	return (dict);
}
