/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 19:05:58 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/05 21:27:27 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *next;

	if (!alst || !del)
		return ;
	if (!(*alst))
		return ;
	tmp = *alst;
	while (tmp)
	{
		next = tmp->next;
		ft_lstdelone(&tmp, del);
		tmp = next;
	}
	*alst = NULL;
}
