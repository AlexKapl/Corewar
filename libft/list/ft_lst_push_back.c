/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 18:29:21 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/02 19:05:13 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_lst_push_back(t_list **alst, t_list *new_node)
{
	t_list	*list;

	list = *alst;
	if (!*alst)
		*alst = new_node;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new_node;
	}
}
