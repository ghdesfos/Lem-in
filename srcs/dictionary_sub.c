/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:00:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/30 18:21:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

size_t		hash(unsigned char *input)
{
	size_t	hashVal;
	int		i;

	if (!input)
		return (0);
	hashVal = 0;
	i = -1;
	while (input[++i])
		hashVal = hashVal * 10 + input[i];
	return (hashVal);
}

int			add_value_to_entree(t_entree *ent, t_entree *valueNode)
{
	t_entree	**values;
	t_entree	**newValues;
	int			len;
	int			i;

	if (!ent || !valueNode)
		return (-1);
	values = ENT_DATA->values;
	len = ENT_DATA->nbValues;
	if (!(newValues = (t_entree**)malloc(sizeof(t_entree*) * (len + 2))))
		return (-1);
	i = -1;
	while (++i < len)
		newValues[i] = values[i];
	newValues[len] = valueNode;
	newValues[len + 1] = NULL;
	free(values);
	ENT_DATA->values = newValues;
	ENT_DATA->nbValues += 1;
	return (1);
}

t_entree	*create_new_entree(t_entree **entrees, char *key)
{
	t_entree 	*ent;
	void		*data;
	static int	vertexNb = 0;

	if (!(ent = (t_entree*)malloc(sizeof(t_entree))))
		return (NULL);
	if (!(data = malloc(sizeof(t_keyvalue))))
		return (NULL);
	ent->data = data;
	ENT_DATA->key = ft_strdup(key);
	ENT_DATA->nbValues = 0;
	if (!(ENT_DATA->values = (t_entree**)malloc(sizeof(t_entree))))
		return (NULL);
	(ENT_DATA->values)[0] = NULL;
	ENT_DATA->vertexNb = vertexNb++;
	ent->next = *entrees;
	*entrees = ent;
	return (ent);
}

t_entree	*find_entree(t_dict *dict, char *key)
{
	int			rk;
	t_entree	*ent;

	rk = (unsigned int)hash((unsigned char*)key) % dict->size;
	ent = *(ENT_NB(rk));
	while (ent)
	{
		if (ft_strcmp(ENT_DATA->key, key) == 0)
			return (ent);
		ent = ent->next;
	}
	return (NULL);
}
