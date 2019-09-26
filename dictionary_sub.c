/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:00:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/09/25 17:43:40 by ghdesfos         ###   ########.fr       */
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
		hashVal = hashVal * 10 + (input - 127);
	if (hashVal < 0)
		return (-hashVal);
	return (hashVal);
}

//	N.B.: in the below functions, check if we should not do some string_dup!!!

//	calculer d'abord le hash, aller au rang donne
//	trouver si la valeur a un node a ce rang
//	si oui, ajouter la valeur dans ce node,...
//	sinon, creer un node, l'ajouter au rang, et ajouter la valeur au node

int			add_value_to_entree(t_entree *ent, char *value)
{
	char	**values;
	char	**newValues;
	int		len;
	int		i;

	values = ENT_DATA->values;
	len = 0;
	while (values[len])
		len++;
	if (!(newValues = (char**)malloc(sizeof(char*) * (len + 2))))
		return (-1);
	i = -1;
	while (++i < len)
		newValues[i] = values[i];
	newValues[len] = value;
	newValues[len + 1] = NULL;
	free(values);
	ENT_DATA->values = newValues;
	return (0);
}

// see comment aboce on string dup

t_entree	*create_new_entree(t_entree **entrees, char *key)
{
	t_entree *ent;

	if (!(ent = (t_entree*)malloc(sizeof(t_entree))))
		return (NULL);
	ENT_DATA->key = key;
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
