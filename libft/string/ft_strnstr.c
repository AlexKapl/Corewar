/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:03:00 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/06 20:12:31 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;
	size_t	x;

	n = ft_strlen((char*)little);
	x = 0;
	if (!*little)
		return ((char*)big);
	while (*big && x < len)
	{
		if (!ft_memcmp(big, little, n))
			if (n + x <= len)
				return ((char*)big);
		big++;
		x++;
	}
	return (0);
}
