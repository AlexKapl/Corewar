/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:18:57 by akaplyar          #+#    #+#             */
/*   Updated: 2017/06/19 17:18:58 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void				*stack_pop(t_list **stack)
{
	t_list			*tmp;
	void			*item;

	if (!*stack)
		return (NULL);
	tmp = *stack;
	*stack = tmp->next;
	item = tmp->content;
	free(tmp);
	return (item);
}

int					stack_push(t_list **stack, void *item, size_t size)
{
	t_list			*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (0);
	new->content = item;
	new->content_size = size;
	new->next = NULL;
	ft_lstadd(stack, new);
	return (1);
}

void				*stack_peek(t_list **stack)
{
	if (!*stack)
		return (NULL);
	else
		return ((*stack)->content);
}
