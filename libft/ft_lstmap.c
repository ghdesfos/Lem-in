/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 20:07:24 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/06/05 11:46:16 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst_head;
	t_list *new_lst;

	if (!lst)
		return (NULL);
	if (!(new_lst_head = (*f)(lst)))
		return (NULL);
	new_lst = new_lst_head;
	lst = lst->next;
	while (lst)
	{
		if (!(new_lst->next = (*f)(lst)))
			return (NULL);
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (new_lst_head);
}
