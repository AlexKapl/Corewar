/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:23:41 by akaplyar          #+#    #+#             */
/*   Updated: 2016/12/08 17:57:58 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*d;

	d = dst;
	while (*src)
	{
		if (!n--)
			return (d);
		*dst++ = *src++;
	}
	while (n--)
		*dst++ = '\0';
	return (d);
}
