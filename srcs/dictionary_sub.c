/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_sub.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:00:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/10/31 18:15:58 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t		hash(unsigned char *input)
{
	size_t	hash_val;
	int		i;

	if (!input)
		return (0);
	hash_val = 0;
	i = -1;
	while (input[++i])
		hash_val = hash_val * 10 + input[i];
	return (hash_val);
}

int			add_value_to_entree(t_entree *ent, t_entree *value_node)
{
	t_entree	**values;
	t_entree	**new_values;
	int			len;
	int			i;

	if (!ent || !value_node)
		return (-1);
	values = ENT_DATA->values;
	len = ENT_DATA->nb_values;
	if (!(new_values = (t_entree**)malloc(sizeof(t_entree*) * (len + 2))))
		return (-1);
	i = -1;
	while (++i < len)
		new_values[i] = values[i];
	new_values[len] = value_node;
	new_values[len + 1] = NULL;
	free(values);
	ENT_DATA->values = new_values;
	ENT_DATA->nb_values += 1;
	return (1);
}

t_entree	*create_new_entree(t_entree **entrees, char *key)
{
	t_entree	*ent;
	void		*data;
	static int	vertex_nb = 0;

	if (!(ent = (t_entree*)malloc(sizeof(t_entree))))
		return (NULL);
	if (!(data = malloc(sizeof(t_keyvalue))))
		return (NULL);
	ent->data = data;
	ENT_DATA->key = ft_strdup(key);
	ENT_DATA->nb_values = 0;
	if (!(ENT_DATA->values = (t_entree**)malloc(sizeof(t_entree))))
		return (NULL);
	(ENT_DATA->values)[0] = NULL;
	ENT_DATA->vertex_nb = vertex_nb++;
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
