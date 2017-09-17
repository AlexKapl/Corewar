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

#include "../includes/stack_queue.h"

static t_list		**get_queue(void)
{
	static t_list	*queue = NULL;

	return (&queue);
}

void				*dequeue(void)
{
	t_list			**queue;
	t_list			*tmp;
	void			*item;

	queue = get_queue();
	if (!*queue)
		return (NULL);
	tmp = *queue;
	item = tmp->content;
	*queue = tmp->next;
	free(tmp);
	return (item);
}

void				enqueue(void *item, size_t size)
{
	t_list			**queue;
	t_list			*temp;

	queue = get_queue();
	temp = *queue;
	ft_lst_push_back(&temp, ft_lstnew(item, size));
	*queue = temp;
}

void				*queue_peek(void)
{
	t_list			**queue;

	queue = get_queue();
	if (!*queue)
		return (NULL);
	else
		return ((*queue)->content);
}
