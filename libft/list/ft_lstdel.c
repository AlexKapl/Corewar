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

static void	ft_only_list_del(void *data, size_t size)
{
	size_t	siz;
	void	*dat;

	siz = size;
	dat = data;
	return ;
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*remove;
	t_list	*tmp;

	remove = *alst;
	if (!del)
		del = &ft_only_list_del;
	while (remove)
	{
		tmp = remove;
		remove = remove->next;
		del((tmp)->content, (tmp)->content_size);
		free(tmp);
	}
	*alst = NULL;
}
