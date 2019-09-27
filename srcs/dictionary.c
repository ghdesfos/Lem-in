/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:58:31 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/27 11:16:18 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		dict_insert(t_dict *dict, char *key, char *value)
{
	int			rk;
	t_entree	*ent;

	if (!dict || !key)
		return (-1);
	rk = (unsigned int)hash((unsigned char*)key) % SIZE_DICT;
	if (NULL == (ent = find_entree(ENT_NB(rk), key)))
	{
		if (NULL == (ent = create_new_entree(ENT_NB(rk), key)))
			return (-1);
	}
	if (-1 == add_value_to_entree(ent, value))
		return (-1);
	return (0);
}

char	**dict_search(t_dict *dict, char *key)
{
	int			rk;
	t_entree	*ent;

	if (!dict || !key)
		return (NULL);
	rk = (unsigned int)hash((unsigned char*)key) % dict->size;
	if (NULL == (ent = find_entree(ENT_NB(rk), key)))
		return (NULL);
	return (ENT_DATA->values);
}

t_dict	*dict_init(int capacity)
{
	t_dict	*dict;
	int		i;

	if (capacity < 1)
		return (NULL);
	if (!(dict = (t_dict*)malloc(sizeof(t_dict))))
		return (NULL);
	dict->size = capacity;
	if (!(dict->entrees = (t_entree**)malloc(sizeof(t_entree*) * (capacity + 1))))
		return (NULL);
	i = -1;
	while (++i < capacity + 1)
		(dict->entrees)[i] = NULL;
	return (dict);
}
