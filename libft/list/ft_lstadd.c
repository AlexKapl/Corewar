/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 14:36:06 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/23 12:44:06 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd(t_list **alst, t_list *new_node)
{
	if (!new_node)
		return ;
	if (*alst)
	{
		new_node->next = *alst;
		*alst = new_node;
	}
	else
		*alst = new_node;
}
