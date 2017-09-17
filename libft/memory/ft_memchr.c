/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:38:06 by akaplyar          #+#    #+#             */
/*   Updated: 2016/11/29 15:12:31 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*str;
	unsigned char		x;

	str = (unsigned char*)s;
	x = (unsigned char)c;
	while (n)
	{
		if (*str == x)
			return (str);
		str++;
		n--;
	}
	return (NULL);
}
