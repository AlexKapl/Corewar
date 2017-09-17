/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 19:46:33 by akaplyar          #+#    #+#             */
/*   Updated: 2017/06/27 18:44:34 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list		*ft_lstnew_struct(void const *content, size_t content_size,
								int (*f)(void const *, size_t, t_list **))
{
	t_list	*node;

	if (!(node = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	node->next = NULL;
	if (!content)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else if (!(f(content, content_size, &node)))
	{
		free(node);
		return (NULL);
	}
	return (node);
}
