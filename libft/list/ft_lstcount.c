/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:26:23 by akaplyar          #+#    #+#             */
/*   Updated: 2017/03/24 19:34:24 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t		ft_lstcount(t_list *begin)
{
	size_t	count;

	count = 0;
	if (begin)
	{
		count = 1;
		while (begin->next)
		{
			count++;
			begin = begin->next;
		}
	}
	return (count);
}
