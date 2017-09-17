/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:36:12 by akaplyar          #+#    #+#             */
/*   Updated: 2016/11/30 16:05:29 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *restrict d, const void *restrict s, int c, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*src;
	unsigned char		z;

	dst = (unsigned char*)d;
	src = (const unsigned char*)s;
	z = (unsigned char)c;
	while (n)
	{
		if (*src == z)
		{
			*dst = *src;
			return (++dst);
		}
		*dst++ = *src++;
		n--;
	}
	return (0);
}
