/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 19:44:38 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/06 19:57:06 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*remove;
	t_list	*tmp;

	remove = *alst;
	if (del)
		while (remove)
		{
			tmp = remove;
			remove = remove->next;
			del((tmp)->content, (tmp)->content_size);
			free(tmp);
		}
	*alst = NULL;
}
