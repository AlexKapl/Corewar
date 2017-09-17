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

#include "../includes/stack_queue.h"

static t_list		**get_stack(void)
{
	static t_list	*stack = NULL;

	return (&stack);
}

void				*stack_pop(void)
{
	t_list			**stack;
	t_list			*tmp;
	void			*item;

	stack = get_stack();
	if (!*stack)
		return (NULL);
	tmp = *stack;
	item = tmp->content;
	*stack = tmp->next;
	free(tmp);
	return (item);
}

void				stack_push(void *item, size_t size)
{
	t_list			**stack;
	t_list			*temp;

	stack = get_stack();
	temp = *stack;
	ft_lstadd(&temp, ft_lstnew(item, size));
	*stack = temp;
}

void				*stack_peek(void)
{
	t_list			**stack;

	stack = get_stack();
	if (!*stack)
		return (NULL);
	else
		return ((*stack)->content);
}
