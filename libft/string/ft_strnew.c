/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 10:52:57 by akaplyar          #+#    #+#             */
/*   Updated: 2017/02/16 17:57:29 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strnew(size_t size)
{
	size_t	i;
	char	*new;

	if (!(new = (char *)malloc(++size)))
		return (NULL);
	i = 0;
	while (i < size)
		new[i++] = '\0';
	return (new);
}
