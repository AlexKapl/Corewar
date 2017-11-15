/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:19:03 by akaplyar          #+#    #+#             */
/*   Updated: 2017/06/19 17:19:04 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void				*dequeue(t_list **queue)
{
	t_list			*tmp;
	void			*item;

	if (!*queue)
		return (NULL);
	tmp = *queue;
	*queue = tmp->next;
	item = tmp->content;
	free(tmp);
	return (item);
}

int					enqueue(t_list **queue, void *item, size_t size)
{
	t_list			*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (0);
	new->content = item;
	new->content_size = size;
	new->next = NULL;
	ft_lst_push_back(queue, new);
	return (1);
}

void				*queue_peek(t_list **queue)
{
	if (!*queue)
		return (NULL);
	else
		return ((*queue)->content);
}
