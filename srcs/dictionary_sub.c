/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:00:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/26 18:05:44 by ghdesfos         ###   ########.fr       */
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

int			add_value_to_entree(t_entree *ent, char *value)
{
	char	**values;
	char	**newValues;
	int		len;
	int		i;

	values = ENT_DATA->values;
	len = 0;
	if (values)
		while (values[len])
			len++;
	if (!(newValues = (char**)malloc(sizeof(char*) * (len + 2))))
		return (-1);
	i = -1;
	while (++i < len)
		newValues[i] = values[i];
	newValues[len] = ft_strdup(value);
	newValues[len + 1] = NULL;
	free(values);
	ENT_DATA->values = newValues;
	return (0);
}

t_entree	*create_new_entree(t_entree **entrees, char *key)
{
	t_entree 	*ent;
	void		*data;

	if (!(ent = (t_entree*)malloc(sizeof(t_entree))))
		return (NULL);
	if (!(data = malloc(sizeof(t_keyvalue))))
		return (NULL);
	ent->data = data;
	ENT_DATA->key = ft_strdup(key);
	ENT_DATA->values = NULL;
	ent->next = *entrees;
	*entrees = ent;
	return (ent);
}

t_entree	*find_entree(t_entree **entrees, char *key)
{
	t_entree *ent;

	ent = *entrees;
	while (ent)
	{
		if (ft_strcmp(ENT_DATA->key, key) == 0)
			return (ent);
		ent = ent->next;
	}
	return (NULL);
}
