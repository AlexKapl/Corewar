/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 14:51:02 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 12:58:14 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*ptr;

	if (!lst || !f)
		return (NULL);
	node = f(lst);
	if (!node)
		return (NULL);
	ptr = node;
	lst = lst->next;
	while (lst)
	{
		node->next = f(lst);
		node = node->next;
		if (!node)
			return (NULL);
		lst = lst->next;
	}
	return (ptr);
}
