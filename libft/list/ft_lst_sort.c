/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 18:46:56 by akaplyar          #+#    #+#             */
/*   Updated: 2017/04/02 18:46:59 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_lst_check_begin(t_list **begin, int (*f)(void *e1, void *e2),
								int *count, int max)
{
	t_list	*cur;
	t_list	*next;

	if (max > 1)
	{
		(*count)++;
		cur = *begin;
		next = cur->next;
		if (f(cur->content, next->content))
		{
			cur->next = next->next;
			next->next = cur;
			*begin = next;
		}
	}
}

void		ft_lst_sort(t_list **begin, int (*f)(void *e1, void *e2),
						int count, int max)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	if (max < 2 || !begin)
		return ;
	ft_lst_check_begin(begin, f, &count, max);
	cur = *begin;
	while (++count < max && cur->next)
	{
		prev = cur;
		cur = cur->next;
		next = cur->next;
		if (f(cur->content, next->content))
		{
			prev->next = next;
			cur->next = next->next;
			next->next = cur;
			cur = next;
		}
	}
	ft_lst_sort(begin, f, 0, max - 1);
}

static void	ft_lst_check_size(t_list **begin, int (*f)(size_t e1, size_t e2),
						int *count, int max)
{
	t_list	*cur;
	t_list	*next;

	if (max > 1)
	{
		(*count)++;
		cur = *begin;
		next = cur->next;
		if (f(cur->content_size, next->content_size))
		{
			cur->next = next->next;
			next->next = cur;
			*begin = next;
		}
	}
}

void		ft_lst_sort_size(t_list **begin, int (*f)(size_t e1, size_t e2),
						int count, int max)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*next;

	if (max < 2 || !begin)
		return ;
	ft_lst_check_size(begin, f, &count, max);
	cur = *begin;
	while (++count < max && cur->next)
	{
		prev = cur;
		cur = cur->next;
		next = cur->next;
		if (f(cur->content_size, next->content_size))
		{
			prev->next = next;
			cur->next = next->next;
			next->next = cur;
			cur = next;
		}
	}
	ft_lst_sort_size(begin, f, 0, max - 1);
}
